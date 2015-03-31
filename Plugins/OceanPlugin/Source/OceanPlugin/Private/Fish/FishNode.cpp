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