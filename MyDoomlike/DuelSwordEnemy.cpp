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

	AttackCollision2 = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision2"));
	AttackCollision2->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("FX_Trail_01_L"));

	AttackCollision2->InitBoxExtent({ 30.f, 5.f, 10.f });
	//Attack2Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnBoxBeginOverlap);
}

void ADuelSwordEnemy::BeginPlay()
{
	Super::BeginPlay();

	AttackCollision2->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);

}

void ADuelSwordEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AIController != nullptr)
	{
		if (AIController->GetCurrentState() == Attacking)
		{
			//AttackCollision2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
			AttackCollision2->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);
		}
		else
		{
			//AttackCollision2->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			AttackCollision2->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);
		}
	}
}
