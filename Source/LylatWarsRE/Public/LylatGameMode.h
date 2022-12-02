// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LylatGameMode.generated.h"

/**
 * 
 */
UCLASS()
class LYLATWARSRE_API ALylatGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	ALylatGameMode(const FObjectInitializer& ObjectInitializer);

	int Score = 0;
public:
	void AddScore(int value);

	UFUNCTION(BlueprintCallable, Category = "Score")
	int GetScore();
};
