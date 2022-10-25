// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class MYDOOMLIKE_API ABasicProjectile : public AActor
{
	GENERATED_BODY()
	
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComp;

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;

public:
	ABasicProjectile();

	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void DealDamage(AActor* MyOwner, AActor* OtherActor);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }


	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		UParticleSystem* ImpactParticles;
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		USoundBase* ImpactSound;


	UPROPERTY(EditAnywhere, Category = Gameplay)
		float MaxRange = 1000;

	UPROPERTY(EditAnywhere, Category = Gameplay)
		float Damage = 10;
};

