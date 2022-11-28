// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LylatPlayerCrosshair.generated.h"

/**
 * 
 */
UCLASS()
class LYLATWARSRE_API ULylatPlayerCrosshair : public UUserWidget
{
	GENERATED_BODY()

		ULylatPlayerCrosshair(const FObjectInitializer& ObjectInitializer);
		~ULylatPlayerCrosshair();
public :
		UPROPERTY(BlueprintReadOnly)
			class ALylatPlayerPawn* PlayerPawn;
		UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
			class UImage* CrosshairImage;
};
