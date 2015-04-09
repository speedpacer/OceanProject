// Fill out your copyright notice in the Description page of Project Settings.

#include "OceanPluginPrivatePCH.h"
#include "Fish/FishFactory.h"
#include "Fish/FishManager.h"
#include "Fish/FishNode.h"
#include "Fish/FlockFish.h"

AFishFactory::AFishFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Allow Ticking
	PrimaryActorTick.bCanEverTick = true;

	// Setup Base
	base = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("FactoryMesh"));
	RootComponent = base;

	// Fish interaction sphere
	FishFactorySphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("FishFactorySphere"));
	FishFactorySphere->SetSphereRadius(5000);
	FishFactorySphere->AttachTo(RootComponent);
	FishFactorySphere->OnComponentBeginOverlap.AddDynamic(this, &AFishFactory::OnBeginOverlap);
	FishFactorySphere->OnComponentEndOverlap.AddDynamic(this, &AFishFactory::OnEndOverlap);

}

void AFishFactory::Tick(float deltaTime)
{
	// Setup Fish Factory
	Setup();

	// Move with Player
	MoveToPlayer();
}

void AFishFactory::OnBeginOverlap(AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	if (otherComp->GetOwner()->GetActorClass() == FishNodeClass)
	{
		// Spawn Fish
		AFishNode *curFishNode = Cast<AFishNode>(otherComp->GetOwner());
		curFishNode->ActivateNode();
	}
}

void AFishFactory::OnEndOverlap(AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex)
{
	if (otherComp->GetOwner()->GetActorClass() == FishNodeClass)
	{
		// Despawn Fish
		AFishNode *curFishNode = Cast<AFishNode>(otherComp->GetOwner());
		curFishNode->DeactivateNode();
	}
}

void AFishFactory::Setup()
{
	if (!isSetup)
	{
		TArray<AActor*> aPlayerList;
		UGameplayStatics::GetAllActorsOfClass(this, PlayerType, aPlayerList);
		if (aPlayerList.Num() > 0)
		{
			Player = aPlayerList[0];
			isSetup = true;
		}
	}
}

void AFishFactory::MoveToPlayer()
{
	if (Player)
	{
		this->SetActorLocation(Player->GetActorLocation());
	}
}