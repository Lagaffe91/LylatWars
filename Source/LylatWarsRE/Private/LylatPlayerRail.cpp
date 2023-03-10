// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatPlayerRail.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"
#include "DebugString.h"
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

	Super::BeginPlay();
}

void ALylatPlayerRail::ComputeRailDistance(float DeltaTime, ALylatEntity* Entity)
{
	if (!Entity || !this->SplineComponent)
	{	
		Debug("Failed compute distance", 0);
		return;
	}

	Entity->EntityRailDistance += DeltaTime * speedMultiplier * railSpeed + PlayerDashSpeed;

	if (RailShouldLoop(Entity))		//May cause problem with loop on rail -> ugly fix : Use end rail event to jump from one classic rail to a looped one....
	{
		if (SplineComponent->IsClosedLoop())
		{
			RailLoop(Entity);
		}
		else
		{
			Entity->RailEnded();
		}
	}
}
