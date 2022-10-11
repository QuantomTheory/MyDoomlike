// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrappleHook.generated.h"

UCLASS()
class MYDOOMLIKE_API AGrappleHook : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrappleHook();

	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void AttachCable(USceneComponent* LaunchPoint);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class APlayerCharacter* OwnerCharacter;

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly)
		class USphereComponent* CollisionComp;

	/** Hook Mesh component */
	UPROPERTY(VisibleDefaultsOnly)
		UStaticMeshComponent* HookMesh;

	/** Hook Mesh component */
	UPROPERTY(VisibleDefaultsOnly)
		class UCableComponent* CableMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent* ProjectileMovement;


	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		USoundBase* ImpactSound;

};
