// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

UCLASS()
class MYDOOMLIKE_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

	virtual void ApplyUpdate(class APlayerCharacter* Character) {};

	virtual void BeginRespawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		class USoundBase* PickupSound;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void EndRespawn();

	void Despawn();


	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		USceneComponent* PickUpRoot;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		class UNiagaraComponent* PickUpNiagara;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUp", meta = (AllowPrivateAccess = "true"))
		class UTP_PickUpComponent* PickUpComponent;


	UPROPERTY(EditAnywhere, Category = "Pickup Details")
		float RespawnTime = 10.f;

	UPROPERTY(EditAnywhere, Category = "Pickup Details")
		float DespawnTime = 3.f;

	UPROPERTY(EditAnywhere, Category = "Pickup Details")
		bool StaticPickup = true;

	FTimerHandle RespawnTimer;

	FTimerHandle DespawnTimer;



};
