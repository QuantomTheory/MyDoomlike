// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_SetAchorLocation.h"
#include "BaseEnemyController.h"
#include "BaseEnemy.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_SetAchorLocation::UBTTaskNode_SetAchorLocation()
{
	NodeName = TEXT("Set Achor Location");
}

// A Behavior Tree Task that triggers the attack for an enemy once in range.
EBTNodeResult::Type UBTTaskNode_SetAchorLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseEnemyController* OwnerController = Cast<ABaseEnemyController>(OwnerComp.GetAIOwner());
	if (OwnerController == nullptr) return EBTNodeResult::Failed;

	ABaseEnemy* EnemyPawn = Cast<ABaseEnemy>(OwnerController->GetPawn());
	if (EnemyPawn == nullptr) return EBTNodeResult::Failed;

	OwnerController->GetBlackboardComponent()->SetValueAsVector(TEXT("AnchorLocation"), EnemyPawn->GetActorLocation());

	return EBTNodeResult::Succeeded;
}



