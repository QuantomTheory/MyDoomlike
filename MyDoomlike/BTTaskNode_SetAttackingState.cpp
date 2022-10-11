// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_SetAttackingState.h"
#include "BaseEnemyController.h"
#include "BaseEnemy.h"

UBTTaskNode_SetAttackingState::UBTTaskNode_SetAttackingState()
{
	NodeName = TEXT("Set Attacking State");
}

// A Behavior Tree Task that triggers the attack for an enemy once in range.
EBTNodeResult::Type UBTTaskNode_SetAttackingState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseEnemyController* OwnerController = Cast<ABaseEnemyController>(OwnerComp.GetAIOwner());
	if (OwnerController == nullptr) return EBTNodeResult::Failed;

	OwnerController->SetCurrentState(Attacking);

	return EBTNodeResult::Succeeded;
}



