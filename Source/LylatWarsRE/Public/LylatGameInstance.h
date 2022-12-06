// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LylatGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LYLATWARSRE_API ULylatGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	ULylatGameInstance();

	UPROPERTY(Category = "Lylat Instance|Game", EditAnywhere, BlueprintReadWrite)
		int Score = 0;

	UPROPERTY(Category = "Lylat Instance|Gyro", EditAnywhere, BlueprintReadWrite)
		bool UseGyro = true;

	UPROPERTY(Category = "Lylat Instance|Gyro", EditAnywhere, BlueprintReadWrite)
		bool GyroFlipX = false;

	UPROPERTY(Category = "Lylat Instance|Gyro", EditAnywhere, BlueprintReadWrite)
		bool GyroFlipY = false;

	UPROPERTY(Category = "Lylat Instance|Gyro", EditAnywhere, BlueprintReadWrite)
		float GyroScale = 3.0f;

	UPROPERTY(Category = "Lylat Instance|Debug", EditAnywhere, BlueprintReadWrite)
		bool DrawDebug = false;
};
