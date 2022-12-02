// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "LylatGenericRail.h"
#include "LylatPlayerRail.generated.h"

/**
 * 
 */
UCLASS()
class LYLATWARSRE_API ALylatPlayerRail : public ALylatGenericRail
{
	GENERATED_BODY()
public : 
	ALylatPlayerRail();

	/*If true, will try his best to posses a player. If it fail will try to spawn the actor specified in ActorToSpawn*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic Rail|Player") //Can change speed on the fly
	bool smartPossess = true;

	/**/
	UPROPERTY(BlueprintReadOnly, Category = "Generic Rail|Player")
		bool isDashing = false;

	UPROPERTY(BlueprintReadOnly, Category = "Generic Rail|Player")
		float PlayerDashSpeed = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ComputeRailDistance(float DeltaTime) override;
};
