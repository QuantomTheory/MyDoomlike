// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickup.h"
#include "Gun.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

void AAmmoPickup::ApplyUpdate(APlayerCharacter* Character)
{
	Character->GetInventoryComp()->GetWeaponOfClass(WeaponType)->AddAmmo(AmmoAmount);

	// Try and play the sound if specified
	if (PickupSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	}
}
