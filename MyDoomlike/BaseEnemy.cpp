// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include <random>
#include "BasePickup.h"
#include "HoardSurvivalGameMode.h"
#include "BaseEnemyController.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AttackCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision"));
	AttackCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("FX_Trail_01_R"));

	AttackCollision->InitBoxExtent({ 18.f, 30.f, 5.f });
	AttackCollision->SetRelativeLocation({ 0.f, 20.f, 0.f });
	//AttackCollision->OnComponentHit.AddDynamic(this, &ABaseEnemy::OnHit);
	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnBoxBeginOverlap);

	// Create a HealthComponent	
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<ABaseEnemyController>(GetInstigatorController());
	AttackCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HealthComp->IsDead())
	{
		IsDead = true;
	}

	if (AIController != nullptr)
	{
		if (AIController->GetCurrentState() == Attacking)
		{
			//AttackCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
			AttackCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
		}
		else
		{
			//AttackCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			AttackCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);
		}
	}
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseEnemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	// Only add impulse and destroy projectile if we hit a physics actor
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (ImpactParticles)
		{
			FRotator ImpactDirection = (-(OtherActor->GetActorLocation() - GetActorLocation())).Rotation();
			UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticles, Hit.ImpactPoint, ImpactDirection);
		}

		if (ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		}

		UClass* DamageTypeClass = UDamageType::StaticClass();
		if (DamageTypeClass == nullptr) return;

		// Apply damage to the impacted actor.
		UGameplayStatics::ApplyDamage(OtherActor, AttackDamage, AIController, this, DamageTypeClass);
	}
}

void ABaseEnemy::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only add impulse and destroy projectile if we hit a physics actor
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		if (ImpactParticles)
		{
			FRotator ImpactDirection = (-(OtherActor->GetActorLocation() - GetActorLocation())).Rotation();
			UGameplayStatics::SpawnEmitterAtLocation(this, ImpactParticles, SweepResult.ImpactPoint, ImpactDirection);
		}

		if (ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		}

		UClass* DamageTypeClass = UDamageType::StaticClass();
		if (DamageTypeClass == nullptr) return;

		// Apply damage to the impacted actor.
		UGameplayStatics::ApplyDamage(OtherActor, AttackDamage, AIController, this, DamageTypeClass);
	}
}

void ABaseEnemy::OnDeath()
{
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 100); // define the range
	if (distr(gen) <= DropChance)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		GetWorld()->SpawnActor<ABasePickup>(ComponentDrop, GetActorLocation(), GetActorRotation(), ActorSpawnParams);
	}

	AHoardSurvivalGameMode* GameMode = Cast<AHoardSurvivalGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->EnemyKilled();
	}

	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}

	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	Destroy();
}


void ABaseEnemy::Attack()
{
	SetIsAttacking(true);
}

// Returns the IsAttacking bool
bool ABaseEnemy::GetIsAttacking() const
{
	return IsAttacking;
}

// Updates the IsAttacking bool
void ABaseEnemy::SetIsAttacking(bool NewValue)
{
	IsAttacking = NewValue;
}