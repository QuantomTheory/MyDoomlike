// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_FocusTarget.generated.h"

/**
 * 
 */
UCLASS()
class MYDOOMLIKE_API UBTTaskNode_FocusTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_FocusTarget();

protected:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
