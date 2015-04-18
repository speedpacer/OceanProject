// Fill out your copyright notice in the Description page of Project Settings.

#include "OceanPluginPrivatePCH.h"
#include "Fish/FishNode.h"
#include "Fish/FishManager.h"
#include "Fish/FlockFish.h"

AFishNode::AFishNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Setup Base
	base = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("NodeMesh"));
	RootComponent = base;

	// Fish node sphere
	FishNodeSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("FishNodeSphere"));
	FishNodeSphere->SetSphereRadius(500);
	FishNodeSphere->AttachTo(RootComponent);
}

void AFishNode::Tick(float val)
{
	if (isFollowingFish)
	{
		this->SetActorLocation(CurLeader->GetActorLocation());
	}

	if (isCurrentlySpawning)
	{
		SpawnFish();
	}
}

void AFishNode::SpawnFish()
{
}

void AFishNode::ActivateNode()
{
	UWorld* const world = GetWorld();
	AFlockFish *leader = NULL;
	FVector spawnLoc = this->GetActorLocation();
	for (int i = 0; i < FishNodeNum; i++)
	{	

		this->SetActorLocation(spawnLoc);
		AFlockFish *aFish = Cast<AFlockFish>(world->SpawnActor(FishNodeType));

		//aFish->SetActorLocation(spawnLoc);
		//spawnLoc = FVector(FMath::FRandRange(spawnLoc.X - (20 * aFish->InteractionSphereRadius), spawnLoc.X + (20 * aFish->InteractionSphereRadius)), 
				//FMath::FRandRange(spawnLoc.Y - (20 * aFish->InteractionSphereRadius), spawnLoc.Y + (20 * aFish->InteractionSphereRadius)), 
				//FMath::FRandRange(spawnLoc.Z - (20 * aFish->InteractionSphereRadius), spawnLoc.Z + (20 * aFish->InteractionSphereRadius)));
		

		aFish->underwaterMax = FVector(spawnLoc.X + 10000, spawnLoc.Y + 10000, spawnLoc.Z + 10000);
		aFish->underwaterMin = FVector(spawnLoc.X - 10000, spawnLoc.Y - 10000, spawnLoc.Z - 10000);
		aFish->isLeader = false;
		aFish->DebugMode = false;

		if (i == 0)
		{
			aFish->isLeader = true;
			leader = aFish;
			CurLeader = aFish;
			spawnLoc = this->GetActorLocation();
		}
		else
		{	
			aFish->leader = leader;
			FishList.Add(aFish);
		}
		aFish->SetActorLocation(spawnLoc);
	}
	
	isFollowingFish = true;
}

void AFishNode::DeactivateNode()
{
	isFollowingFish = false;

	while (FishList.Num() != 0)
	{
		FishList.Pop()->K2_DestroyActor();
	}

	CurLeader->K2_DestroyActor();
	CurLeader = NULL;
}