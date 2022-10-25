// Fill out your copyright notice in the Description page of Project Settings.


#include "DuelSwordEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "BaseEnemyController.h"

ADuelSwordEnemy::ADuelSwordEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sets up a second collision box for the second sword.
	AttackCollision2 = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision2"));
	AttackCollision2->SetupAttachment(GetMesh(), TEXT("FX_Trail_01_L"));
	AttackCollision2->InitBoxExtent({ 30.f, 5.f, 10.f });
	AttackCollision2->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnBoxBeginOverlap);
}

void ADuelSwordEnemy::BeginPlay()
{
	Super::BeginPlay();

	// Same as AttackCollision from BaseEnemy class.
	AttackCollision2->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);

}

void ADuelSwordEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AIController != nullptr)
	{
		if (AIController->GetCurrentState() == Attacking)
		{
			// Same as AttackCollision from BaseEnemy class.
			AttackCollision2->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
		}
		else
		{
			// Same as AttackCollision from BaseEnemy class.
			AttackCollision2->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);
		}
	}
}
