// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Gun.h"
#include "PlayerCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner());

	Weapon1 = GetWorld()->SpawnActor<AGun>(Weapon1Class);
	Weapon1->AttachWeapon(Character);
	Weapon1->SetActorHiddenInGame(true);

	Weapon2 = GetWorld()->SpawnActor<AGun>(Weapon2Class);
	Weapon2->AttachWeapon(Character);
	Weapon2->SetActorHiddenInGame(true);

	Weapon3 = GetWorld()->SpawnActor<AGun>(Weapon3Class);
	Weapon3->AttachWeapon(Character);
	Weapon3->SetActorHiddenInGame(true);

	Weapon4 = GetWorld()->SpawnActor<AGun>(Weapon4Class);
	Weapon4->AttachWeapon(Character);
	Weapon4->SetActorHiddenInGame(true);

}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AGun* UInventoryComponent::GetCurrentWeapon()
{
	return CurrentWeapon;
}

void UInventoryComponent::SetCurrentWeapon(int32 WeaponSlot)
{
	switch (WeaponSlot)
	{
	case 1:
		CurrentWeapon = Weapon1;
		break;
	case 2:
		CurrentWeapon = Weapon2;
		break;
	case 3:
		CurrentWeapon = Weapon3;
		break;
	case 4:
		CurrentWeapon = Weapon4;
		break;
	}
}

void UInventoryComponent::ReloadCurrentWeapon()
{
	CurrentWeapon->LoadClip();
}

AGun* UInventoryComponent::GetWeaponOfClass(TSubclassOf<AGun> InWeaponClass)
{
	if (InWeaponClass == Weapon1Class)
	{
		return Weapon1;
	}
	else if (InWeaponClass == Weapon2Class)
	{
		return Weapon2;
	}
	else if(InWeaponClass == Weapon3Class)
	{
		return Weapon3;
	}
	else if(InWeaponClass == Weapon4Class)
	{
		return Weapon4;
	}
	else
	{
		return Weapon1;
	}
}
