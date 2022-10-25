// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_GetTargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class MYDOOMLIKE_API UBTTaskNode_GetTargetLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_GetTargetLocation();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};