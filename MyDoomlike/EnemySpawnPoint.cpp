// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"
#include "Kismet/KismetMathLibrary.h"
#include <random>
#include "Kismet/GameplayStatics.h"
#include "HoardSurvivalGameMode.h"
#include "TimerManager.h"

// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Builds the Mesh and Spawn point of the Actor.
	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawner Mesh"));
	RootComponent = SpawnerMesh;

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AHoardSurvivalGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawnPoint::SetupWave(int32 CurrentWave)
{
	WaveSpawnRate = BaseSpawnRate - CurrentWave;
	if (WaveSpawnRate <= SpawnRateDeviation*2)
	{
		WaveSpawnRate = SpawnRateDeviation * 2;
	}

	StartSpawnTimer();
}

void AEnemySpawnPoint::StartSpawnTimer()
{
	// Starts a countdown to spawn the next enemy, with a random deviation.
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr((WaveSpawnRate - SpawnRateDeviation), (WaveSpawnRate + SpawnRateDeviation)); // define the range

	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AEnemySpawnPoint::SpawnEnemy, distr(gen));
}

void AEnemySpawnPoint::SpawnEnemy()
{
	// Checks if all enemy limit has been reached yet.
	if (GameMode->CanSpawnEnemy())
	{
		FVector SpawnLocation = SpawnPoint->GetComponentLocation();
		FRotator SpawnRotator = SpawnPoint->GetComponentRotation();

		GetWorld()->SpawnActor<ABaseEnemy>(SpawningCharacter, SpawnLocation, SpawnRotator);
		UGameplayStatics::SpawnEmitterAtLocation(this, SpawnEffect, SpawnLocation, SpawnRotator);

		StartSpawnTimer();
	}
}

