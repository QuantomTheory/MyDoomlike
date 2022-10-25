// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_SetWalkSpeed.h"
#include "BaseEnemyController.h"
#include "BaseEnemy.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTaskNode_SetWalkSpeed::UBTTaskNode_SetWalkSpeed()
{
	NodeName = TEXT("Set Walk Speed");
}

// A Behavior Tree Task that triggers the attack for an enemy once in range.
EBTNodeResult::Type UBTTaskNode_SetWalkSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseEnemyController* OwnerController = Cast<ABaseEnemyController>(OwnerComp.GetAIOwner());
	if (OwnerController == nullptr) return EBTNodeResult::Failed;

	ABaseEnemy* EnemyPawn = Cast<ABaseEnemy>(OwnerController->GetPawn());
	if (EnemyPawn == nullptr) return EBTNodeResult::Failed;

	EnemyPawn->GetCharacterMovement()->MaxWalkSpeed = OwnerController->GetBlackboardComponent()->GetValueAsFloat(*NewSpeedVariableName);


	return EBTNodeResult::Succeeded;
}



