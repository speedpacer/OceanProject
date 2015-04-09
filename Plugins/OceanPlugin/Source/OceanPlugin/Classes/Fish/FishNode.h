// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OceanPluginPrivatePCH.h"
#include "GameFramework/Actor.h"
#include "Fish/FlockFish.h"
#include "FishNode.generated.h"

/**
*
*/
UCLASS()
class AFishNode : public AActor
{
	GENERATED_BODY()

	/** Static mesh component */
	class UStaticMeshComponent* base;

	/** Fish node sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* FishNodeSphere;
	
	// is the fish node updating to fish leader's location?
	bool isFollowingFish = false;

	// is the fish node updating to fish leader's location?
	bool isCurrentlySpawning = false;

public:

	/** Constructor */
	AFishNode(const FObjectInitializer& ObjectInitializer);

	// Type of Fish Node
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fish Factory Attributes")
	UClass* FishNodeType;

	// Number of fish in node
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fish Factory Attributes")
	float FishNodeNum;

	// Spawn the fishes 
	void ActivateNode();

	// Despawn the fishes
	void DeactivateNode();

protected:

	/** Overrided tick function */
	virtual void Tick(float val) override;

	AFlockFish* CurLeader;

	TArray<AFlockFish*> FishList;

	void SpawnFish();

	float SpawnedFish = 0;


};