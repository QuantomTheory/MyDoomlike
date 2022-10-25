// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHealthComponent::Heal(float AmountHealed)
{
	CurrentHealth += AmountHealed;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	AActor* Owner = GetOwner();
	if (Owner != nullptr)
	{
		// Sets the DamageTaken Function to be triggered when the Owner takes Damage
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	}
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentHealth > MaxHealth)
	{
		int32 Overhealth = CurrentHealth - MaxHealth;
		// Decrease the Overheath by an amount depending on how much overhealth there is, to a minimum loss rate.
		CurrentHealth -= DeltaTime  * (((Overhealth/OverhealthLossRate) > MinOverhealthLoss) ? (Overhealth / OverhealthLossRate) : MinOverhealthLoss);
	}
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	// Prevents the Player from damaging themselves
	if (DamagedActor != nullptr && DamageCauser != nullptr && DamagedActor == DamageCauser) return;

	if (Damage <= 0.f) return;

	// If the character has health remaining, subtract the damage.
	if (CurrentHealth > 0.f)
	{
		CurrentHealth -= Damage;
	}
}