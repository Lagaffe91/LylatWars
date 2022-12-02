// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatPlayerRail.h"

#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"
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

void ALylatPlayerRail::ComputeRailDistance(float DeltaTime)
{
	railTime += (DeltaTime * speedMultiplier * railSpeed) + PlayerDashSpeed;

	if (RailShouldLoop())	//May cause problem with loop on rail -> ugly fix : Use end rail event to jump from one classic rail to a looped one....
	{
		if (this->SplineComponent->IsClosedLoop())
		{
			RailLoop();
		}
		else
		{
			this->RailIsOver = true;
			this->RailEnded();
		}
	}
}
