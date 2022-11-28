// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatPlayerRail.h"

ALylatPlayerRail::ALylatPlayerRail(): ALylatGenericRail()
{
}

void ALylatPlayerRail::BeginPlay()
{
	if (smartPossess)
	{
		this->ActorsOnRail.Add(GetWorld()->GetFirstPlayerController()->GetPawn());
	}
	else
	{
		this->SpawnActorsOnRail();
	}

	Super::BeginPlay();
}