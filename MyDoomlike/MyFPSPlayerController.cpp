// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFPSPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMyFPSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// SetUp and Show the Start Screen Widget
	HUD = CreateWidget(this, HUDClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}

}