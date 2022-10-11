// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class AGun;
class UHealthComponent;
class UInventoryComponent;
class USpringArmComponent;
class UGrappleHookComponent;
class AGrappleLauncher;

// Declaration of the delegate that will be called when the Primary Action is triggered
// It is declared as dynamic so it can be accessed also in Blueprints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);

UCLASS()
class MYDOOMLIKE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

// FUNCTIONS
public:
	// Sets default values for this character's properties
	APlayerCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns FP_Mesh subobject **/
	UFUNCTION(BlueprintCallable, Category = "Components")
		USkeletalMeshComponent* GetFP_Mesh() const { return FP_Mesh; }
	/** Returns FirstPersonCameraComponent subobject **/
	UFUNCTION(BlueprintCallable, Category = "Components")
		UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	/** Returns HealthComp subobject **/
	UFUNCTION(BlueprintCallable, Category = "Components")
		UHealthComponent* GetHealthComponent() const { return HealthComp; }
	/** Returns FirstPersonCameraComponent subobject **/
	UFUNCTION(BlueprintCallable, Category = "Components")
		UInventoryComponent* GetInventoryComp() const { return InventoryComp; }
	/** Returns FirstPersonCameraComponent subobject **/
	UFUNCTION(BlueprintCallable, Category = "Components")
		AGrappleLauncher* GetGrappleLauncher() const { return GrappleLauncher; }

	FVector LookTrace(float Range);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Fires a projectile.
	void StartPrimaryAction();
	UFUNCTION(BlueprintCallable)
		void FinishPrimaryAction();


	void StartSecondaryAction();
	UFUNCTION(BlueprintCallable)
		void FinishSecondaryAction();

	// Cycles through Weapons
	void CycleWeapon();

	// Cycles through Weapons
	void EquipWeapon();

	// Cycles through Weapons
	void UnequipWeapon();

	// ReloadsCurrentWeapon
	void ReloadWeapon();

	// Handles moving forward/backward
	void MoveForward(float Val);

	// Handles strafing movement, left and right 
	void MoveRight(float Val);


	void OnDeath();

	// VARIABLES
private:
	// Mesh for the Pawns arms
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
		USkeletalMeshComponent* FP_Mesh;

	// 1st Person Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY()
		UCharacterMovementComponent* MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UInventoryComponent* InventoryComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AGrappleLauncher> GrappleLauncherClass;

	UPROPERTY()
		AGrappleLauncher* GrappleLauncher;

	int32 CurrentWeaponSlot = 1;

	UPROPERTY()
		UAnimInstance* CharacterAnimInstance;

	/** AnimMontage to play each time we reload */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		UAnimMontage* EquipWeaponAnimation;

	/** AnimMontage to play each time we reload */
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		UAnimMontage* UnequipWeaponAnimation;


	float EquipTime;

	FTimerHandle EquipTimer;

	void EnableEquippedGun();
};
