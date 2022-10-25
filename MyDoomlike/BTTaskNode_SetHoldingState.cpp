// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_SetHoldingState.h"
#include "BaseEnemyController.h"
#include "BaseEnemy.h"

UBTTaskNode_SetHoldingState::UBTTaskNode_SetHoldingState()
{
	NodeName = TEXT("Set Holding State");
}

// A Behavior Tree Task that triggers the attack for an enemy once in range.
EBTNodeResult::Type UBTTaskNode_SetHoldingState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseEnemyController* OwnerController = Cast<ABaseEnemyController>(OwnerComp.GetAIOwner());
	if (OwnerController == nullptr) return EBTNodeResult::Failed;

	OwnerController->SetCurrentState(Holding);

	return EBTNodeResult::Succeeded;
}



