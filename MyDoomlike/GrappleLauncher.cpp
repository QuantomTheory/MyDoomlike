// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleLauncher.h"
#include "PlayerCharacter.h"
#include "GrappleHook.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AGrappleLauncher::AGrappleLauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("AttachPoint"));
	RootComponent = AttachPoint;

	LauncherMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LauncherMesh"));
	LauncherMesh->SetupAttachment(AttachPoint);

	LaunchPoint = CreateDefaultSubobject<USceneComponent>(TEXT("LaunchPoint"));
	LaunchPoint->SetupAttachment(LauncherMesh);

}

// Called when the game starts or when spawned
void AGrappleLauncher::BeginPlay()
{
	Super::BeginPlay();
	if (ReelSound)
	{
		ReelSoundComponent = UGameplayStatics::SpawnSoundAttached(ReelSound, LaunchPoint);
		ReelSoundComponent->Stop();
	}
}

// Called every frame
void AGrappleLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsRetracting)
	{
		double RopeLength = FVector::Distance(GrapplePoint, Character->GetActorLocation());
		if (RopeLength <= MinGrappleDistance)
		{
			Release();
		}
		else
		{
			Character->GetCharacterMovement()->AddImpulse((((GrapplePoint - Character->GetActorLocation()).GetSafeNormal(0.0001)) * (GrappleRate * DeltaTime)), true);
		}
	}
}

void AGrappleLauncher::Launch()
{

	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and fire a projectile
	if (Hook != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			FVector ProjectileTargetLocation = Character->LookTrace(MaxGrappleDistance);
			FVector SpawnLocation = LaunchPoint->GetComponentLocation();

			// Uses these to get a direction to aim the projectile at.
			FRotator SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnLocation, ProjectileTargetLocation);;

			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			SpawnLocation = SpawnLocation + SpawnRotation.Vector();

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			// Spawn the projectile at the muzzle
			HookActor = World->SpawnActor<AGrappleHook>(Hook, SpawnLocation, SpawnRotation, ActorSpawnParams);
			HookActor->SetOwner(Character);
			HookActor->AttachCable(LaunchPoint);
		}
	}

	// Try and play the sound if specified
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, LaunchPoint->GetComponentLocation());
	}
}

void AGrappleLauncher::Retract(FVector GrappleLocation)
{
	GrapplePoint = GrappleLocation;
	IsRetracting = true;
	Character->GetCharacterMovement()->GroundFriction = 0;
	if (ReelSoundComponent != nullptr)
	{
		ReelSoundComponent = UGameplayStatics::SpawnSoundAttached(ReelSound, LaunchPoint);
		ReelSoundComponent->Play();
	}
}

void AGrappleLauncher::Release()
{
	IsRetracting = false;
	HookActor->Destroy();
	Character->GetCharacterMovement()->GroundFriction = DefaultFriction;
	// Try and play the sound if specified
	if (ReelSoundComponent != nullptr)
	{
		ReelSoundComponent->Stop();
	}
}

void AGrappleLauncher::AttachLauncher(APlayerCharacter* InCharacter)
{
	Character = InCharacter;
	if (Character != nullptr)
	{
		// Attach the weapon to the First Person Character
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
		this->AttachToComponent(Character->GetFP_Mesh(), AttachmentRules, TEXT("LauncherAttachPoint"));
		this->SetOwner(Character);

		DefaultFriction = Character->GetCharacterMovement()->GroundFriction;
	}
}



