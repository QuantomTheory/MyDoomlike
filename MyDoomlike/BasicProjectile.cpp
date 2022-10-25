// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ABasicProjectile::ABasicProjectile()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("PlayerProjectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ABasicProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 10000.f;
	ProjectileMovement->MaxSpeed = 10000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ABasicProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}

	if (ImpactParticles)
	{
		FRotator ImpactDirection = (-(Hit.ImpactPoint - GetActorLocation())).Rotation();
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticles, Hit.ImpactPoint, ImpactDirection);
	}

	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, Hit.ImpactPoint);
	}

	ACharacter* HitCharacter = Cast<ACharacter>(OtherActor);

	// Only deal damage if we hit a character
	if ((HitCharacter != nullptr) && (OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor != MyOwner) && (MyOwner != nullptr))
	{
		DealDamage(MyOwner, OtherActor);
	}

	Destroy();
}

void ABasicProjectile::DealDamage(AActor* MyOwner, AActor* OtherActor)
{
	// Get the projectile Controller, and DamageType and ensure they're not null pointers.
	AController* InstigatorController = MyOwner->GetInstigatorController();
	if (InstigatorController == nullptr) return;

	UClass* DamageTypeClass = UDamageType::StaticClass();
	if (DamageTypeClass == nullptr) return;

	// Apply damage to the impacted actor.
	UGameplayStatics::ApplyDamage(OtherActor, Damage, InstigatorController, this, DamageTypeClass);
}