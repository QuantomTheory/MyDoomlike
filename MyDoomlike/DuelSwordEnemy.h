// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "DuelSwordEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MYDOOMLIKE_API ADuelSwordEnemy : public ABaseEnemy
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADuelSwordEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* AttackCollision2;
	
};
