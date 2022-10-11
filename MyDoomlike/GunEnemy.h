// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "GunEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MYDOOMLIKE_API AGunEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGunEnemy();

	UFUNCTION(BlueprintCallable)
		virtual void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABasicProjectile> AmmoType;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		UParticleSystem* MuzzleFlashAnimation;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float FireInterval = 0.5;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float ShotDitributionAngle = 2.f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float MaxRange = 1000.f;
	
};
