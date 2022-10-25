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
	/* This function is empty to allow different functionality to be added to different child gamemodes.
	
	Not made a pure virtual function so that this gamemode could be used in the menu level and this class could be called without something happening.*/
}