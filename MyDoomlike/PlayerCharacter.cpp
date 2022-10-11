// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "BasicProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Gun.h"
#include "HealthComponent.h"
#include "InventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GrappleLauncher.h"
#include "HoardSurvivalGameMode.h"
#include "Kismet/GameplayStatics.h"
#include <memory>

APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;


	FP_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	FP_Mesh->SetOnlyOwnerSee(true);
	FP_Mesh->SetupAttachment(FirstPersonCameraComponent);
	FP_Mesh->bCastDynamicShadow = false;
	FP_Mesh->CastShadow = false;
	FP_Mesh->SetRelativeRotation(FRotator(0.f, -90.f, 5.f));
	FP_Mesh->SetRelativeLocation(FVector(16.f, 0.f, -178.f));;

	// Create a HealthComponent	
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	// Create a InventoryComponent	
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	

	MoveComp = GetCharacterMovement();
	if (MoveComp != nullptr)
	{
		JumpMaxHoldTime = 0.25;

		MoveComp->MaxWalkSpeed = 1000;
		MoveComp->MaxWalkSpeedCrouched = 600;
		MoveComp->JumpZVelocity = 400;
		MoveComp->AirControl = 0.8;
		MoveComp->FallingLateralFriction = 0.2;
	}
}

void APlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	CurrentWeaponSlot = 1;
	InventoryComp->SetCurrentWeapon(CurrentWeaponSlot);

	CharacterAnimInstance = FP_Mesh->GetAnimInstance();
	// Attach the Owner Gun to the Actor
	EquipWeapon();

	// Create a GrappleHookComp	
	GrappleLauncher = GetWorld()->SpawnActor<AGrappleLauncher>(GrappleLauncherClass);
	GrappleLauncher->AttachLauncher(this);

	CharacterAnimInstance = FP_Mesh->GetAnimInstance();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HealthComp->IsDead())
	{
		OnDeath();
	}
}
//////////////////////////////////////////////////////////////////////////// Input

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerCharacter::MoveRight);

	// Bind fire event
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &APlayerCharacter::StartPrimaryAction);
	PlayerInputComponent->BindAction("PrimaryAction", IE_Released, this, &APlayerCharacter::FinishPrimaryAction);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("SwapWeapon", IE_Pressed, this, &APlayerCharacter::UnequipWeapon);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::ReloadWeapon);


	PlayerInputComponent->BindAction("SecondaryAction", IE_Pressed, this, &APlayerCharacter::StartSecondaryAction);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Released, this, &APlayerCharacter::FinishSecondaryAction);
}

void APlayerCharacter::StartPrimaryAction()
{
	// Trigger the OnItemUsed Event
	InventoryComp->GetCurrentWeapon()->PullTrigger();

}

void APlayerCharacter::FinishPrimaryAction()
{
	// Trigger the OnItemUsed Event
	InventoryComp->GetCurrentWeapon()->ReleaseTrigger();
	
}

void APlayerCharacter::StartSecondaryAction()
{
	GrappleLauncher->Launch();
}

void APlayerCharacter::FinishSecondaryAction()
{
	GrappleLauncher->Release();
}

void APlayerCharacter::CycleWeapon()
{
	// Try and play a ReloadAnimation if specified
	InventoryComp->GetCurrentWeapon()->SetActorHiddenInGame(true);

	InventoryComp->SetCurrentWeapon(CurrentWeaponSlot);

	EquipWeapon();
}

void APlayerCharacter::EquipWeapon()
{
	InventoryComp->GetCurrentWeapon()->SetActorHiddenInGame(false);
	InventoryComp->GetCurrentWeapon()->ReleaseTrigger();
	// Try and play a ReloadAnimation if specified
	if (EquipWeaponAnimation != nullptr && CharacterAnimInstance != nullptr)
	{
		EquipTime = (EquipWeaponAnimation->GetPlayLength()) / 1.5;
		CharacterAnimInstance->Montage_Play(EquipWeaponAnimation, 1.f);
	}
	GetWorldTimerManager().SetTimer(EquipTimer, this, &APlayerCharacter::EnableEquippedGun, EquipTime);
	
}

void APlayerCharacter::UnequipWeapon()
{

	if (++CurrentWeaponSlot > 4) CurrentWeaponSlot = 1;
	InventoryComp->GetCurrentWeapon()->ReleaseTrigger();
	// Try and play a ReloadAnimation if specified
	UnequipWeaponAnimation->GetPlayLength();
	if (UnequipWeaponAnimation != nullptr && CharacterAnimInstance != nullptr)
	{
		EquipTime = (UnequipWeaponAnimation->GetPlayLength()) / 1.5;
		CharacterAnimInstance->Montage_Play(UnequipWeaponAnimation, 1.f);
	}
	GetWorldTimerManager().SetTimer(EquipTimer, this, &APlayerCharacter::CycleWeapon, EquipTime);
}

void APlayerCharacter::ReloadWeapon()
{
	InventoryComp->ReloadCurrentWeapon();
}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void APlayerCharacter::OnDeath()
{
	AHoardSurvivalGameMode* HoardMode = Cast<AHoardSurvivalGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (HoardMode)
	{
		HoardMode->GameOver();
		Destroy();
	}
	AMyDoomlikeGameMode* TutorialMode = Cast<AMyDoomlikeGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (TutorialMode)
	{
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("MenuLevel"));
	}
}

void APlayerCharacter::EnableEquippedGun()
{
	InventoryComp->GetCurrentWeapon()->EnableWeapon();
}

FVector APlayerCharacter::LookTrace(float Range)
{
	FVector ViewpointLocation;
	FRotator ViewpointRotation;
	GetController()->GetPlayerViewPoint(ViewpointLocation, ViewpointRotation);

	FHitResult HitResult;
	FVector End = ViewpointLocation + (ViewpointRotation.Vector() * Range);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, ViewpointLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params))
	{
		return HitResult.ImpactPoint;
	}
	else
	{
		return ViewpointLocation + (ViewpointRotation.Vector() * Range);
	}
}