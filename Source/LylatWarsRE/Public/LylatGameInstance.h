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

	UPROPERTY(Category = "Lylat Instance|Game", VisibleAnywhere)
		int Score = 0;

	UPROPERTY(Category = "Lylat Instance|Gyro", VisibleAnywhere)
		bool UseGyro = true;

	UPROPERTY(Category = "Lylat Instance|Gyro", VisibleAnywhere)
		bool GyroFlipX = false;

	UPROPERTY(Category = "Lylat Instance|Gyro", VisibleAnywhere)
		bool GyroFlipY = false;

	UPROPERTY(Category = "Lylat Instance|Gyro", VisibleAnywhere)
		float GyroScale = 3.0f;
};
