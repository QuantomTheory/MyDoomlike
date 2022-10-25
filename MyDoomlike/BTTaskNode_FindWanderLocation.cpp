// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_FindWanderLocation.h"
#include "BaseEnemyController.h"
#include "BaseEnemy.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

/* Gets a location nearby to wander towards while the enemy waits to go in for an attack.*/

UBTTaskNode_FindWanderLocation::UBTTaskNode_FindWanderLocation()
{
	NodeName = TEXT("Find Wander Location");
}

// A Behavior Tree Task that triggers the attack for an enemy once in range.
EBTNodeResult::Type UBTTaskNode_FindWanderLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseEnemyController* OwnerController = Cast<ABaseEnemyController>(OwnerComp.GetAIOwner());
	if (OwnerController == nullptr) return EBTNodeResult::Failed;

	ABaseEnemy* EnemyPawn = Cast<ABaseEnemy>(OwnerController->GetPawn());
	if (EnemyPawn == nullptr) return EBTNodeResult::Failed;

	FVector OriginLocation = OwnerController->GetBlackboardComponent()->GetValueAsVector("AnchorLocation");
	FVector WanderLocation = UNavigationSystemV1::GetRandomReachablePointInRadius(GetWorld(), OriginLocation, 200);

	OwnerController->GetBlackboardComponent()->SetValueAsVector(TEXT("WanderLocation"), WanderLocation);

	return EBTNodeResult::Succeeded;
}

