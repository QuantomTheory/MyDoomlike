// Fill out your copyright notice in the Description page of Project Settings.


#include "AoE_Projectile.h"
#include "Kismet/GameplayStatics.h"

void AAoE_Projectile::DealDamage(AActor* MyOwner, AActor* OtherActor)
{
	// Get the projectile Controller, and DamageType and ensure they're not null pointers.
	AController* InstigatorController = MyOwner->GetInstigatorController();
	if (InstigatorController == nullptr) return;

	UClass* DamageTypeClass = UDamageType::StaticClass();
	if (DamageTypeClass == nullptr) return;

	// Set the projectile owner as an Ignored Actor for the Damage Function
	TArray<AActor*> IgnoredActors = { MyOwner };

	// Apply Radial Damage on Impact
	UGameplayStatics::ApplyRadialDamageWithFalloff(GetWorld(), Damage, MinDamage, GetActorLocation(), InnerImpactRadius, OuterImpactRadius, DamageFalloff, DamageTypeClass, IgnoredActors, this, InstigatorController, ECollisionChannel::ECC_WorldStatic);
}
