// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyDoomlikeGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMyDoomlikeGameMode::AMyDoomlikeGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/MyAssets/Characters/PlayerCharacter/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


void AMyDoomlikeGameMode::EnemyKilled()
{
	//UE_LOG(LogTemp, Warning, TEXT("GameModeBase PawnKilled() Function Called"))
}