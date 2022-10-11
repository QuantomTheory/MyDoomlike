// Fill out your copyright notice in the Description page of Project Settings.


#include "GunEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include <random>
#include "BasicProjectile.h"
#include "BaseEnemyController.h"

AGunEnemy::AGunEnemy()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGunEnemy::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Enemy Fire"));
	// Try and fire a projectile
	if (AmmoType != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FVector ProjectileTargetLocation = AIController->GetTargetActor()->GetActorLocation();
			FVector SpawnLocation = GetMesh()->GetSocketLocation(TEXT("Muzzle_Front"));

			// Uses these to get a direction to aim the projectile at.
			FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, ProjectileTargetLocation);

			std::random_device rd; // obtain a random number from hardware
			std::mt19937 gen(rd()); // seed the generator
			std::uniform_int_distribution<> distr((0 - ShotDitributionAngle), ShotDitributionAngle); // define the range
			SpawnRotation.Pitch += distr(gen);
			SpawnRotation.Yaw += distr(gen);

			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			SpawnLocation = SpawnLocation + SpawnRotation.Vector();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// Spawn the projectile at the muzzle
			ABasicProjectile* ProjectileActor = World->SpawnActor<ABasicProjectile>(AmmoType, SpawnLocation, SpawnRotation, ActorSpawnParams);
			if (ProjectileActor != nullptr)
			{
				ProjectileActor->SetOwner(this);
			}
		}
	}

	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetMesh()->GetSocketLocation(TEXT("Muzzle_Front_XForward")));
	}

	// Try and play a firing animation if specified
	if (MuzzleFlashAnimation != nullptr)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlashAnimation, GetMesh(), TEXT("Muzzle_Front_XForward"));
	}
}

void AGunEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AGunEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
