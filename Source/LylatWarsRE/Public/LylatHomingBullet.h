// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LylatNormalBullet.h"
#include "LylatHomingBullet.generated.h"

/**
 * 
 */
UCLASS()
class LYLATWARSRE_API ALylatHomingBullet : public ALylatNormalBullet
{
	GENERATED_BODY()
	ALylatHomingBullet(const FObjectInitializer& ObjectInitializer);

public:
	void HomingTarget(const AActor *Object);
};
