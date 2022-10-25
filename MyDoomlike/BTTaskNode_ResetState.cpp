// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_ResetState.h"
#include "BaseEnemyController.h"
#include "BaseEnemy.h"

UBTTaskNode_ResetState::UBTTaskNode_ResetState()
{
	NodeName = TEXT("Reset State");
}

// A Behavior Tree Task that triggers the attack for an enemy once in range.
EBTNodeResult::Type UBTTaskNode_ResetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseEnemyController* OwnerController = Cast<ABaseEnemyController>(OwnerComp.GetAIOwner());
	if (OwnerController == nullptr) return EBTNodeResult::Failed;

	OwnerController->SetCurrentState(Moving);

	return EBTNodeResult::Succeeded;
}

