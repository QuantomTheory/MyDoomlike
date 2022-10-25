// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "PlayerCharacter.h"
#include "HealthComponent.h"
#include "HealthPickup.h"
#include "Kismet/GameplayStatics.h"

void AHealthPickup::ApplyUpdate(APlayerCharacter* Character)
{
	Character->GetHealthComponent()->Heal(HealthAmount);

	// Try and play the sound if specified
	if (PickupSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}
}

