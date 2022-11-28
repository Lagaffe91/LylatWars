// Fill out your copyright notice in the Description page of Project Settings.

#include "LylatPlayerCrosshair.h"

#include "Kismet/GameplayStatics.h"

#include "LylatPlayerPawn.h"

ULylatPlayerCrosshair::ULylatPlayerCrosshair(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	PlayerPawn = (ALylatPlayerPawn*)UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!PlayerPawn)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, this->GetName() + TEXT(" : Crosshair widget : Failed to retrive player ref"));
	}
}

ULylatPlayerCrosshair::~ULylatPlayerCrosshair()
{

}