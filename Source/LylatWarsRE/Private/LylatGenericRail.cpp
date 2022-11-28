// Fill out your copyright notice in the Description page of Project Settings.

#include "LylatGenericRail.h"

#include "DebugString.h"
#include "Components/SplineComponent.h"

// Sets default values
ALylatGenericRail::ALylatGenericRail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	InitRail();
}

// Called when the game starts or when spawned
void ALylatGenericRail::BeginPlay()
{
	Super::BeginPlay();
	
	this->SpawnActorsOnRail();
}

// Called every frame
void ALylatGenericRail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RailIsOver)
	{
		return;
	}

	if (railStartDelay > 0)
	{
		railStartDelay -= DeltaTime;
	}
	else
	{
		railTime += DeltaTime * speedMultiplier * railSpeed;
		
		if(RailShouldLoop())
		{
			if(SplineComponent->IsClosedLoop()) //Rail is loop
			{ 
				RailLoop();
			}
			else
			{
				this->RailEnded_Implementation();
				this->RailEnded();
			}
		}
	}

	this->UpdateAllActorsTransform(railTime);
}

void ALylatGenericRail::JoinRail(TSubclassOf<AActor> Actor)
{
	if (Actor)
	{
		ActorsOnRail.Add(Actor.GetDefaultObject());
	}
}

void ALylatGenericRail::JoinRailArray(TArray<AActor*> Actors)
{
	this->ActorsOnRail += Actors;
}

void ALylatGenericRail::RailEnded_Implementation()
{
	this->RailIsOver = true;
}

bool ALylatGenericRail::RailShouldLoop()
{
	return railTime > SplineComponent->GetSplineLength();
}

void ALylatGenericRail::RailLoop()
{
	railTime /= SplineComponent->GetSplineLength();
}

void ALylatGenericRail::InitRail()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	RootComponent = SplineComponent;
}

void ALylatGenericRail::SpawnActorsOnRail()
{
	if (!SpawnActor)
		return;

	if (SplineComponent)
	{
		for (TSubclassOf<AActor> actor : ActorsToSpawn)
		{
			AActor*actorPtr = GetWorld()->SpawnActor<AActor>(actor, this->SplineComponent->GetTransformAtDistanceAlongSpline(0, ESplineCoordinateSpace::World));
			
			if (!actorPtr)
			{
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, this->GetName() + TEXT(" : Rail : Actor not correctly spawned"));
			}
			else
			{
				ActorsOnRail.Add(actorPtr);
			}
		}
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, this->GetName() + TEXT(" : Rail : Spline component is wrong (not created ?)"));
	}
}

void ALylatGenericRail::UpdateActorTransform(TSubclassOf<AActor> Actor, const float& Time)
{
	UpdateActorTransform(Actor.GetDefaultObject(), Time);
}

void ALylatGenericRail::UpdateActorTransform(AActor* Actor, const float& Time)
{
	if (Actor && this->SplineComponent)
	{
		Actor->SetActorTransform(this->SplineComponent->GetTransformAtDistanceAlongSpline(Time, ESplineCoordinateSpace::World));
	}
}

void ALylatGenericRail::UpdateAllActorsTransform(const float& Time)
{
	for (AActor* Actor : ActorsOnRail)
	{
		UpdateActorTransform(Actor, Time);
	}
}