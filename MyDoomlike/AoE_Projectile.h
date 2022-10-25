// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasicProjectile.h"
#include "AoE_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class MYDOOMLIKE_API AAoE_Projectile : public ABasicProjectile
{
	GENERATED_BODY()
	
private:
	virtual void DealDamage(AActor* MyOwner, AActor* OtherActor) override;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float InnerImpactRadius = 100;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float OuterImpactRadius = 250;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float DamageFalloff = 2;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float MinDamage = Damage/2;

};
