// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "HitScan_Gun.generated.h"

/**
 * 
 */
UCLASS()
class MYDOOMLIKE_API AHitScan_Gun : public AGun
{
	GENERATED_BODY()

protected:
	/** Make the weapon Fire a Projectile */
	virtual void Fire() override;

private:
	bool GunTrace(FHitResult& OutHitResult, FVector& OutShotDirection);

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		UParticleSystem* HitParticles;
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		int32 ShotCount = 20;
};
