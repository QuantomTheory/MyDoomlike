// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.generated.h"

UCLASS()
class MYDOOMLIKE_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called every frame
	void SetupWave(int32 CurrentWave);

	void StartSpawnTimer();


private:
	class AHoardSurvivalGameMode* GameMode;

	// ACTOR COMPONENTS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		USceneComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals", meta = (AllowPrivateAccess = "true"))
		class UParticleSystem* SpawnEffect;


	// Minion ENEMY SPAWNING
	void SpawnEnemy();

	// The Class of the melee character to be spawned
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mechanics", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABaseEnemy> SpawningCharacter;

	FTimerHandle SpawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
		float BaseSpawnRate = 15.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
		float WaveSpawnRate;

	float SpawnRateDeviation = 3.f;
};
