// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYDOOMLIKE_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay();
	void ShowCurrentWave();
	void ShowWaveEnd();
	void ShowWinGame();
	void ShowLoseGame();
	void RemoveScreens();

private:

	// The Widget Classes
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HUDClass;

	// The Widget Classes
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> CurrentWaveClass;

	// The Widget Classes
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WaveEndClass;

	// The Widget Classes
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> WinGameClass;

	// The Widget Classes
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> LoseGameClass;


	UPROPERTY()
		class UUserWidget* HUD;
	UPROPERTY()
		class UUserWidget* CurrentWaveScreen;
	UPROPERTY()
		class UUserWidget* WaveEndScreen;
	UPROPERTY()
		class UUserWidget* WinScreen;
	UPROPERTY()
		class UUserWidget* LoseScreen;

};