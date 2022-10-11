// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyDoomlikeGameMode.generated.h"

UCLASS(minimalapi)
class AMyDoomlikeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyDoomlikeGameMode();

public:
	virtual void EnemyKilled();

};
