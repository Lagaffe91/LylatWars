// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LylatEnemy.h"
#include "LylatAdoEnemy.generated.h"

/**
 * 
 */
UCLASS()
class LYLATWARSRE_API ALylatAdoEnemy : public ALylatEnemy
{
	GENERATED_BODY()
	

public : 
	void Behaviour_Implementation(float DeltaTime)	override;

	void Animate_Implementation(float DeltaTime) override;

};
