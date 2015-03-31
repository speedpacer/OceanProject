// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OceanPluginPrivatePCH.h"
#include "GameFramework/Actor.h"
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

public:

	/** Constructor */
	AFishNode(const FObjectInitializer& ObjectInitializer);

	// Type of Fish Node
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fish Factory Attributes")
	UClass* FishNodeType;

	// Number of fish in node
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fish Factory Attributes")
	float FishNodeNum;


};