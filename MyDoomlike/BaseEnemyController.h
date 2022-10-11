// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyController.generated.h"



UENUM(BlueprintType)
enum AI_State
{
	Moving,
	Holding,
	Attacking
};
/**
 * 
 */
UCLASS()
class MYDOOMLIKE_API ABaseEnemyController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Components")
	AActor* GetTargetActor() const;
	UFUNCTION(BlueprintCallable, Category = "Components")
	AI_State GetCurrentState() const;
	UFUNCTION(BlueprintCallable, Category = "Components")
	void SetCurrentState(AI_State NewState);

private:
	// The Behavior Tree Blueprint Class for Enemy AI Behavior
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* AIBehavior;

	// The TargetClass for the Enemy
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AActor> TargetClass;

	AActor* TargetActor;

	AI_State Current_State;
	UBlackboardComponent* Blackboard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float MaxWalkSpeed = 650;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float WanderWalkSpeed = 650;
};