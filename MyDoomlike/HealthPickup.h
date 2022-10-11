// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "HealthPickup.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class MYDOOMLIKE_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void ApplyUpdate(APlayerCharacter* Character) override;

private:


	UPROPERTY(EditAnywhere, Category = "Pickup Details")
		int32 HealthAmount;
	
};
