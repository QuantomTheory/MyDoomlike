// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FocusTarget.h"
#include "BaseEnemyController.h"
#include "BaseEnemy.h"
#include "PlayerCharacter.h"

UBTTaskNode_FocusTarget::UBTTaskNode_FocusTarget()
{
	NodeName = TEXT("Focus Target");
}

// A Behavior Tree Task that triggers the attack for an enemy once in range.
EBTNodeResult::Type UBTTaskNode_FocusTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseEnemyController* OwnerController = Cast<ABaseEnemyController>(OwnerComp.GetAIOwner());
	if (OwnerController == nullptr) return EBTNodeResult::Failed;

	ABaseEnemy* EnemyPawn = Cast<ABaseEnemy>(OwnerController->GetPawn());
	if (EnemyPawn == nullptr) return EBTNodeResult::Failed;

	APlayerCharacter* TargetActor = Cast<APlayerCharacter>(OwnerController->GetTargetActor());
	if (TargetActor == nullptr) return EBTNodeResult::Failed;

	OwnerController->SetFocus(TargetActor);

	return EBTNodeResult::Succeeded;
}



