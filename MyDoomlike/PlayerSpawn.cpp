// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpawn.h"
#include "Kismet/KismetMathLibrary.h"
#include <random>
#include "Kismet/GameplayStatics.h"
#include "HoardSurvivalGameMode.h"

// Sets default values
APlayerSpawn::APlayerSpawn()
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
void APlayerSpawn::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerSpawn::SpawnPlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawn Player"));

	FVector SpawnLocation = SpawnPoint->GetComponentLocation();
	FRotator SpawnRotator = SpawnPoint->GetComponentRotation();

	GetWorld()->SpawnActor<APlayerCharacter>(SpawningCharacter, SpawnLocation, SpawnRotator);
	UGameplayStatics::SpawnEmitterAtLocation(this, SpawnEffect, SpawnLocation, SpawnRotator);
}

