// Fill out your copyright notice in the Description page of Project Settings.


#include "HoardSurvivalGameMode.h"
#include "ShooterPlayerController.h"
#include "EngineUtils.h"
#include "BaseEnemyController.h"
#include "TimerManager.h"
#include "EnemySpawnPoint.h"
#include "PlayerSpawn.h"
#include "Kismet/GameplayStatics.h"

void AHoardSurvivalGameMode::EnemyKilled()
{
	Super::EnemyKilled();

	KilledEnemyCount++;

	if (KilledEnemyCount >= MaxEnemyCount)
		EndWave();
}

bool AHoardSurvivalGameMode::CanSpawnEnemy()
{
	if (SpawnedEnemyCount < MaxEnemyCount)
	{
		SpawnedEnemyCount++;
		return true;
	}
	
	return false;
}

void AHoardSurvivalGameMode::BeginPlay()
{
	PlayerController = Cast<AShooterPlayerController>(GetWorld()->GetFirstPlayerController());
	StartWave();
}

void AHoardSurvivalGameMode::StartWave()
{
	PlayerController->RemoveScreens();

	PlayerController->BeginPlay();
	PlayerController->ShowCurrentWave();
	MaxEnemyCount = CurrentWave * BaseEnemyCount;

	SpawnedEnemyCount = 0;
	KilledEnemyCount = 0;
	for (AEnemySpawnPoint* SpawnPoint : TActorRange<AEnemySpawnPoint>(GetWorld()))
	{
		SpawnPoint->SetupWave(CurrentWave);
	}

	GetWorldTimerManager().SetTimer(WaveTimer, this, &AHoardSurvivalGameMode::GameOver, WaveLength);
}

void AHoardSurvivalGameMode::EndWave()
{
	CurrentWave++;

	GetWorldTimerManager().ClearTimer(WaveTimer);
	if (CurrentWave <= 5)
	{
		GetWorldTimerManager().SetTimer(WaveRestartTimer, this, &AHoardSurvivalGameMode::StartWave, WaveRestartTime);
		PlayerController->ShowWaveEnd();
		return;
	}
	
	PlayerWins = true;
	GameOver();
}

void AHoardSurvivalGameMode::GameOver()
{
	if (PlayerWins)
	{
		PlayerController->ShowWinGame();
		GetWorldTimerManager().SetTimer(WaveRestartTimer, this, &AHoardSurvivalGameMode::EndGame, WaveRestartTime);
	}
	else
	{
		PlayerController->ShowLoseGame();
		GetWorldTimerManager().SetTimer(WaveRestartTimer, this, &AHoardSurvivalGameMode::EndGame, WaveRestartTime);
	}
}

void AHoardSurvivalGameMode::EndGame()
{
	PlayerController->RemoveScreens();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MenuLevel"));
}

int32 AHoardSurvivalGameMode::GetRemainingEnemies()
{
	return MaxEnemyCount-KilledEnemyCount;
}

float AHoardSurvivalGameMode::GetRemainingWaveTime()
{
	return GetWorldTimerManager().GetTimerRemaining(WaveTimer);
}

float AHoardSurvivalGameMode::GetRemainingRestartTime()
{
	return GetWorldTimerManager().GetTimerRemaining(WaveRestartTimer);
}
