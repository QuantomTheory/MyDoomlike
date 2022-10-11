// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

class UHealthComponent;

UCLASS()
class MYDOOMLIKE_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseEnemy();

	UFUNCTION(BlueprintCallable)
		bool GetIsAttacking() const;

	UFUNCTION(BlueprintCallable)
		void SetIsAttacking(bool NewValue);

	UFUNCTION(BlueprintCallable)
		virtual void Attack();

	UFUNCTION(BlueprintCallable)
		bool GetIsDead() const { return IsDead; };

	UFUNCTION(BlueprintCallable)
		void OnDeath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ABaseEnemyController* AIController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* AttackCollision;

	bool IsAttacking = false;

	// The damage dealt by the melee attack
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spell List", meta = (AllowPrivateAccess = "true"))
		float AttackDamage = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		UParticleSystem* ImpactParticles;
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		USoundBase* ImpactSound;

	UPROPERTY(EditDefaultsOnly, Category = Death)
		UParticleSystem* DeathParticles;
	UPROPERTY(EditDefaultsOnly, Category = Death)
		USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category = Death)
		bool IsDead;


	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		TSubclassOf<class ABasePickup> ComponentDrop;
	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
		float DropChance = 50.f;
};
