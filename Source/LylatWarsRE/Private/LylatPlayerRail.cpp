// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatPlayerRail.h"

#include "Kismet/GameplayStatics.h"
#include "LylatPlayerPawn.h"

ALylatPlayerRail::ALylatPlayerRail(): ALylatGenericRail()
{
}

void ALylatPlayerRail::BeginPlay()
{
	if (smartPossess)
	{
		ALylatPlayerPawn* player = (ALylatPlayerPawn*)UGameplayStatics::GetActorOfClass(GetWorld(), ALylatPlayerPawn::StaticClass());
		this->ActorsOnRail.Add(player);
	}
	else
	{
		this->SpawnActorsOnRail();
	}

	Super::BeginPlay();
}