// Fill out your copyright notice in the Description page of Project Settings.


#include "HitScan_Gun.h"
#include "PlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include <random>

void AHitScan_Gun::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}
	for (int32 i = 0; i < ShotCount; i++)
	{
		FVector ShotDirection;
		FHitResult HitResult;
		if (GunTrace(HitResult, ShotDirection))
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, HitResult.ImpactPoint, ShotDirection.Rotation());
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, HitResult.ImpactPoint);
			if (HitResult.GetActor())
			{
				

				FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);

				AController* OwnerController = GetOwnerController();
				if (OwnerController == nullptr) return;

				HitResult.GetActor()->TakeDamage(Damage, DamageEvent, OwnerController, this);

			}
		}
	}
	

	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}

	// Try and play a firing animation if specified
	if (CharacterFireAnimation != nullptr)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* CharacterAnimInstance = Character->GetFP_Mesh()->GetAnimInstance();
		if (CharacterAnimInstance != nullptr)
		{
			CharacterAnimInstance->Montage_Play(CharacterFireAnimation, 1.f);
		}
	}// Try and play a firing animation if specified
	if (MuzzleFlashAnimation != nullptr)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlashAnimation, GunMesh, TEXT("muzzle"));
	}
}

bool AHitScan_Gun::GunTrace(FHitResult& OutHitResult, FVector& OutShotDirection)
{

	FVector MuzzleLocation = GunMesh->GetSocketLocation(TEXT("muzzle"));

	FVector ProjectileTargetLocation = Character->LookTrace(MaxRange);

	// Uses these to get a direction to aim the projectile at.
	FRotator MuzzleRotation = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, ProjectileTargetLocation);

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr((0-ShotDitributionAngle), ShotDitributionAngle); // define the range
	MuzzleRotation.Pitch += distr(gen);
	MuzzleRotation.Yaw += distr(gen);

	OutShotDirection = -MuzzleRotation.Vector();

	FVector End = MuzzleLocation + (MuzzleRotation.Vector() * MaxRange);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(OutHitResult, MuzzleLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}