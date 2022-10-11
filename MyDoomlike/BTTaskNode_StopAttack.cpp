// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_StopAttack.h"
#include "BaseEnemyController.h"
#include "BaseEnemy.h"

UBTTaskNode_StopAttack::UBTTaskNode_StopAttack()
{
	NodeName = TEXT("Stop Attack");
}

// A Behavior Tree Task that triggers the attack for an enemy once in range.
EBTNodeResult::Type UBTTaskNode_StopAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseEnemyController* OwnerController = Cast<ABaseEnemyController>(OwnerComp.GetAIOwner());
	if (OwnerController == nullptr) return EBTNodeResult::Failed;

	ABaseEnemy* EnemyPawn = Cast<ABaseEnemy>(OwnerController->GetPawn());
	if (EnemyPawn == nullptr) return EBTNodeResult::Failed;

	EnemyPawn->SetIsAttacking(false);

	return EBTNodeResult::Succeeded;
}

