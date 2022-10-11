// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "PlayerCharacter.h"
#include "BasicProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include <random>

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunRoot = CreateDefaultSubobject<USceneComponent>(TEXT("GunRoot"));
	RootComponent = GunRoot;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(GunRoot);

}

FName AGun::GetWeaponName() const
{
	return WeaponName;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	CurrentClipAmmo = MaxClipAmmo;
	CurrentStoredAmmo = MaxStoredAmmo;
}

void AGun::PullTrigger()
{
	TriggerPressed = true;
}

void AGun::ReleaseTrigger()
{
	TriggerPressed = false;
	FireDelta = FireInterval;
}

void AGun::LoadClip()
{
	int32 AmmoNeeded = MaxClipAmmo - CurrentClipAmmo;

	if (CurrentStoredAmmo == 0 || AmmoNeeded == 0)
	{
		return;
	}
	else 
	{
		if (AmmoNeeded > CurrentStoredAmmo)
		{
			CurrentClipAmmo += CurrentStoredAmmo;
			CurrentStoredAmmo = 0;
		}
		else if (AmmoNeeded <= CurrentStoredAmmo)
		{
			CurrentClipAmmo += AmmoNeeded;
			CurrentStoredAmmo -= AmmoNeeded;
		}

		// Try and play a ReloadAnimation if specified
		if (ReloadAnimation != nullptr)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* CharacterAnimInstance = Character->GetFP_Mesh()->GetAnimInstance();
			if (CharacterAnimInstance != nullptr)
			{
				DisableWeapon();
				ReloadTime = (ReloadAnimation->GetPlayLength()) / 2;
				CharacterAnimInstance->Montage_Play(ReloadAnimation, 1.f);
			}

			// Try and play the sound if specified
			if (ReloadSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GunMesh->GetComponentLocation());
			}
			GetWorldTimerManager().SetTimer(ReloadTimer, this, &AGun::EnableWeapon, ReloadTime);
		}
	}
}

void AGun::DisableWeapon()
{
	WeaponEnabled = false;
}

void AGun::EnableWeapon()
{
	WeaponEnabled = true;
}

void AGun::AddAmmo(int32 AmmoAmount)
{
	CurrentStoredAmmo += AmmoAmount;
	if (CurrentStoredAmmo > MaxStoredAmmo)
	{
		CurrentStoredAmmo = MaxStoredAmmo;
	}
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WeaponEnabled == true && TriggerPressed == true)
	{
		// Only count the time between each shot on Full Auto
		if (IsFullAuto)
		{
			FireDelta += DeltaTime;
		}
		if (FireDelta >= FireInterval)
		{
			if (CurrentClipAmmo > 0)
			{
				Fire();

				CurrentClipAmmo--;
			}
			else
			{
				// Try and play the sound if specified
				if (EmptySound != nullptr)
				{
					UGameplayStatics::PlaySoundAtLocation(this, EmptySound, GunMesh->GetSocketLocation(TEXT("muzzle")));
				}
			}
			
			FireDelta = 0;
		}
		
		
	}
		
}

void AGun::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and fire a projectile
	if (AmmoType != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			FVector ProjectileTargetLocation = Character->LookTrace(MaxRange);
			FVector SpawnLocation = GunMesh->GetSocketLocation(TEXT("muzzle"));

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
				ProjectileActor->SetOwner(GetOwner());
			}
		}
	}

	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GunMesh->GetSocketLocation(TEXT("muzzle")));
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

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}

void AGun::AttachWeapon(APlayerCharacter* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character != nullptr)
	{
		// Attach the weapon to the First Person Character
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		this->AttachToComponent(Character->GetFP_Mesh(), AttachmentRules, TEXT("GripPoint"));
		this->SetOwner(Character);

		// Register so that Fire is called every time the character tries to use the item being held
		//Character->OnUseItem.AddDynamic(this, &AGun::Fire);
		//Character->SetWeaponToCurrentSlot(this);
	}
}