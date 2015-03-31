// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OceanPluginPrivatePCH.h"
#include "GameFramework/Actor.h"
#include "FishFactory.generated.h"

/**
*
*/
UCLASS()
class AFishFactory : public AActor
{
	GENERATED_BODY()

	/** Static mesh component */
	class UStaticMeshComponent* base;

	/** Fish factory sphere */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* FishFactorySphere;

public:

	/** Constructor */
	AFishFactory(const FObjectInitializer& ObjectInitializer);

	// Max Fish in Factory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fish Factory Attributes")
	float MaxFish = 1200.0;

	// Player Type to Attach to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fish Factory Attributes")
	UClass* PlayerType;

	// Fish Node Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fish Factory Attributes")
	UClass* FishNodeClass;

	// Player
	AActor* Player;

private:

	/** Overrided tick function */
	virtual void Tick(float deltaTime) override;

	UFUNCTION()
	void OnBeginOverlap(AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnEndOverlap(AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex);

	/* Setup the Fish Node */
	void Setup();

	/* Move Fish Factory to Player*/
	void MoveToPlayer();

	bool isSetup = false;


};