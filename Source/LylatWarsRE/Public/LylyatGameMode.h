// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LylyatGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LYLATWARSRE_API ALylyatGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	ALylyatGameMode(const FObjectInitializer& ObjectInitializer);

	int Score = 0;
public:
	void AddScore(int value);
};
