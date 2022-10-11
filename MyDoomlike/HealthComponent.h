// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYDOOMLIKE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION()
		bool IsDead() const { return CurrentHealth <= 0; };

	UFUNCTION()
		void Heal(float AmountHealed);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// Maximum Health
	UPROPERTY(EditAnywhere, Category = "Health")
		float MaxHealth = 100;

	// Current Health
	UPROPERTY(VisibleAnywhere, Category = "Health")
		float CurrentHealth = 0.f;

	UFUNCTION()
		void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);

	UFUNCTION(BlueprintPure)
		float GetHealthPercent() const { return CurrentHealth / MaxHealth; }

	UFUNCTION(BlueprintPure)
		float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintPure)
		float GetMaxHealth() const { return MaxHealth; }

	UPROPERTY(EditAnywhere, Category = "Health")
		float OverhealthLossRate = 5.f;

	UPROPERTY(EditAnywhere, Category = "Health")
		float MinOverhealthLoss = 1.f;
		
};
