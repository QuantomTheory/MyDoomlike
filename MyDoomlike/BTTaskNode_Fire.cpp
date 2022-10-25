// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Fire.h"
#include "BaseEnemyController.h"
#include "GunEnemy.h"

UBTTaskNode_Fire::UBTTaskNode_Fire()
{
	NodeName = TEXT("Fire");
}

// A Behavior Tree Task that triggers the attack for an enemy once in range.
EBTNodeResult::Type UBTTaskNode_Fire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseEnemyController* OwnerController = Cast<ABaseEnemyController>(OwnerComp.GetAIOwner());
	if (OwnerController == nullptr) return EBTNodeResult::Failed;

	AGunEnemy* EnemyPawn = Cast<AGunEnemy>(OwnerController->GetPawn());
	if (EnemyPawn == nullptr) return EBTNodeResult::Failed;

	EnemyPawn->Fire();

	return EBTNodeResult::Succeeded;
}

