// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrappleLauncher.generated.h"

UCLASS()
class MYDOOMLIKE_API AGrappleLauncher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrappleLauncher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Launch();

	void Retract(FVector GrappleLocation);

	void Release();

	void AttachLauncher(class APlayerCharacter* InCharacter);

private:
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AGrappleHook> Hook;

	// SceneComponent for the Target Point
	UPROPERTY(VisibleDefaultsOnly, Category = "Targeting")
		USceneComponent* AttachPoint;

	/** Hook Mesh component */
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* LauncherMesh;

	// SceneComponent for the Target Point
	UPROPERTY(VisibleDefaultsOnly, Category = "Targeting")
		USceneComponent* LaunchPoint;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		USoundBase* ReelSound;

	class UAudioComponent* ReelSoundComponent;

	APlayerCharacter* Character;

	AGrappleHook* HookActor;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		float GrappleRate = 200;

	bool IsRetracting = false;

	FVector GrapplePoint;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		float MinGrappleDistance = 300;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		float MaxGrappleDistance = 3000;

	float DefaultFriction;

};
