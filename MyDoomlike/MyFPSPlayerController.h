// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyFPSPlayerController.generated.h"

class UUserWidget;
/**
 * 
 */
UCLASS()
class MYDOOMLIKE_API AMyFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay();

private:

	// The Widget Classes
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HUDClass;


	UPROPERTY()
		class UUserWidget* HUD;
	
};
