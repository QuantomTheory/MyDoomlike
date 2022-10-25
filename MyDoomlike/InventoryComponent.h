// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AGun;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYDOOMLIKE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UFUNCTION(BlueprintCallable, Category = "Components")
	 AGun* GetCurrentWeapon();
	void SetCurrentWeapon(int32 WeaponSlot);

	void ReloadCurrentWeapon();

	AGun* GetWeaponOfClass(TSubclassOf<AGun> InWeaponClass);

private:
	AGun* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventroy", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AGun> Weapon1Class;
	AGun* Weapon1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventroy", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AGun> Weapon2Class;
	AGun* Weapon2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventroy", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AGun> Weapon3Class;
	AGun* Weapon3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventroy", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AGun> Weapon4Class;
	AGun* Weapon4;
};

