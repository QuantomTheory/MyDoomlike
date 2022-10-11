// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyDoomlikeGameMode.h"
#include "HoardSurvivalGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYDOOMLIKE_API AHoardSurvivalGameMode : public AMyDoomlikeGameMode
{
	GENERATED_BODY()

public:
	virtual void EnemyKilled() override;
	bool CanSpawnEnemy();

	virtual void BeginPlay() override;
	void GameOver();

private:
	void StartWave();
	void EndWave();


	void EndGame();

	class AShooterPlayerController* PlayerController;

	bool PlayerWins;

	int32 CurrentWave = 1;

	UFUNCTION(BlueprintCallable)
		int32 GetCurrentWave() { return CurrentWave; }

	UPROPERTY(EditDefaultsOnly)
		int32 BaseEnemyCount = 10;
	UPROPERTY(VisibleAnywhere)
		int32 MaxEnemyCount;

	int32 SpawnedEnemyCount = 0;

	int32 KilledEnemyCount = 0;

	UFUNCTION(BlueprintCallable)
		int32 GetRemainingEnemies();

	UPROPERTY(EditAnywhere)
		float WaveLength = 180.f;

	FTimerHandle WaveTimer;


	UFUNCTION(BlueprintCallable)
		float GetRemainingWaveTime();

	UPROPERTY(EditAnywhere)
		float WaveRestartTime = 10.f;

	FTimerHandle WaveRestartTimer;


	UFUNCTION(BlueprintCallable)
		float GetRemainingRestartTime();
};
