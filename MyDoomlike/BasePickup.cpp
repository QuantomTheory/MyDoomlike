// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickup.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "TimerManager.h"
#include "TP_PickUpComponent.h"

// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickUpRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PickUpRoot"));
	RootComponent = PickUpRoot;

	PickUpNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PickUpNiagara"));
	PickUpNiagara->SetupAttachment(PickUpRoot);

	// Create a HealthComponent	
	PickUpComponent = CreateDefaultSubobject<UTP_PickUpComponent>(TEXT("Pick Up"));
	PickUpComponent->SetupAttachment(PickUpNiagara);

}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
	// If the pickup was dropped by an enemy on death it will begin a despawn timer.
	if (!StaticPickup)
	{
		GetWorldTimerManager().SetTimer(DespawnTimer, this, &ABasePickup::Despawn, DespawnTime);
	}
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePickup::BeginRespawn()
{
	PickUpNiagara->SetVisibility(false);
	PickUpComponent->SetGenerateOverlapEvents(false);
	if (StaticPickup)
	{
		GetWorldTimerManager().SetTimer(RespawnTimer, this, &ABasePickup::EndRespawn, RespawnTime);
	}
	else
	{
		Destroy();
	}
}

void ABasePickup::EndRespawn()
{
	PickUpNiagara->SetVisibility(true);
	PickUpComponent->SetGenerateOverlapEvents(true);
}

void ABasePickup::Despawn()
{
	Destroy();
}

