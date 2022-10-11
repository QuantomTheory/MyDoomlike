// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyDoomlikeGameMode.h"
#include "BaseEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

// Setup the Behavior Tree and Blackboard values for the Enemy AI Behavior Tree
void ABaseEnemyController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		Blackboard = GetBlackboardComponent();

		TargetActor = UGameplayStatics::GetActorOfClass(GetWorld(), TargetClass);
		if (Blackboard)
		{
			if (TargetActor)
			{
				Blackboard->SetValueAsObject(TEXT("Target"), TargetActor);
				Blackboard->SetValueAsVector(TEXT("TargetLocation"), TargetActor->GetActorLocation());
			}
			
			Blackboard->SetValueAsFloat(TEXT("MaxWalkSpeed"), MaxWalkSpeed);
			
			Blackboard->SetValueAsFloat(TEXT("WanderWalkSpeed"), WanderWalkSpeed);

			SetCurrentState(Moving);
		}
		
	}
}

void ABaseEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Return the Target Actor Pointer
AActor* ABaseEnemyController::GetTargetActor() const
{
	return TargetActor;
}

AI_State ABaseEnemyController::GetCurrentState() const
{
	return Current_State;
}

void ABaseEnemyController::SetCurrentState(AI_State NewState)
{
	Current_State = NewState;
	GetBlackboardComponent()->SetValueAsEnum(TEXT("AIState"), Current_State);
}
