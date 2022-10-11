// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// SetUp and Show the Start Screen Widget
	HUD = CreateWidget(this, HUDClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}

}

void AShooterPlayerController::ShowCurrentWave()
{
	CurrentWaveScreen = CreateWidget(this, CurrentWaveClass);
	if (CurrentWaveScreen)
	{
		CurrentWaveScreen->AddToViewport();
	}
}

void AShooterPlayerController::ShowWaveEnd()
{
	if (CurrentWaveScreen)
	{
		CurrentWaveScreen->RemoveFromViewport();
	}
	WaveEndScreen = CreateWidget(this, WaveEndClass);
	if (WaveEndScreen)
	{
		WaveEndScreen->AddToViewport();
	}
}

void AShooterPlayerController::ShowWinGame()
{
	if (CurrentWaveScreen)
	{
		CurrentWaveScreen->RemoveFromViewport();
	}
	WinScreen = CreateWidget(this, WinGameClass);
	if (WinScreen)
	{
		WinScreen->AddToViewport();
	}
}

void AShooterPlayerController::ShowLoseGame()
{
	if (CurrentWaveScreen)
	{
		CurrentWaveScreen->RemoveFromViewport();
	}
	LoseScreen = CreateWidget(this, LoseGameClass);
	if (LoseScreen)
	{
		LoseScreen->AddToViewport();
	}
}

void AShooterPlayerController::RemoveScreens()
{
	if (WaveEndScreen)
	{
		WaveEndScreen->RemoveFromViewport();
	}
	if (WinScreen)
	{
		WinScreen->RemoveFromViewport();
	}
	if (LoseScreen)
	{
		LoseScreen->RemoveFromViewport();
	}
}

