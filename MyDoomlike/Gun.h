// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class APlayerCharacter;

UCLASS()
class MYDOOMLIKE_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	UFUNCTION(BlueprintCallable, Category = "Details")
		FName GetWeaponName() const;

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void PullTrigger();

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		void ReleaseTrigger();

	void LoadClip();
	void DisableWeapon();
	void EnableWeapon();

	void AddAmmo(int32 AmmoAmount);


	UFUNCTION(BlueprintCallable, Category = "Ammunition")
		int32 GetCurrentClipAmmo() const { return CurrentClipAmmo; }

	UFUNCTION(BlueprintCallable, Category = "Ammunition")
		int32 GetMaxClipAmmo() const { return MaxClipAmmo; }

	UFUNCTION(BlueprintCallable, Category = "Ammunition")
		int32 GetCurrentStoredAmmo() const { return CurrentStoredAmmo; }

	UFUNCTION(BlueprintCallable, Category = "Ammunition")
		int32 GetMaxStoredAmmo() const { return MaxStoredAmmo; }

	int32 GetRange() const { return MaxRange; }

	void AttachWeapon(APlayerCharacter* TargetCharacter);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Details")
		FName WeaponName = "Gun";

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		USceneComponent* GunRoot;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		USkeletalMeshComponent* GunMesh;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABasicProjectile> AmmoType;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		UAnimMontage* CharacterFireAnimation;

	/** AnimMontage to play each time we reload */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		UAnimMontage* ReloadAnimation;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		USoundBase* ReloadSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		UParticleSystem* MuzzleFlashAnimation;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		USoundBase* EmptySound;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float FireInterval = 0.5;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		bool IsFullAuto = false;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float ShotDitributionAngle = 2.f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float MaxRange = 1000.f;

	AController* GetOwnerController() const;

	/** The Character holding this weapon*/
	APlayerCharacter* Character;

	bool WeaponEnabled = false;

	bool TriggerPressed = false;

	float FireDelta = FireInterval;




	UPROPERTY(VisibleAnywhere, Category = Gameplay)
		int32 CurrentClipAmmo;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		int32 MaxClipAmmo = 10;

	UPROPERTY(VisibleAnywhere, Category = Gameplay)
		int32 CurrentStoredAmmo;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		int32 MaxStoredAmmo = 10;


	float ReloadTime;

	FTimerHandle ReloadTimer;
};
