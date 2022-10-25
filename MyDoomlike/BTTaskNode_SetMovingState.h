// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_SetMovingState.generated.h"

/**
 * 
 */
UCLASS()
class MYDOOMLIKE_API UBTTaskNode_SetMovingState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_SetMovingState();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};