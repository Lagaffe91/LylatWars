// Fill out your copyright notice in the Description page of Project Settings.

#include "LylatGenericRail.h"

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
	
	this->SpawnActorOnRail();
}

// Called every frame
void ALylatGenericRail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (railStartDelay > 0)
	{
		railStartDelay -= DeltaTime;
	}
	else
	{
		railTime += DeltaTime * speedMultiplier * railSpeed;
		this->UpdateActorTransform(railTime);
	}
}

void ALylatGenericRail::InitRail()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	RootComponent = SplineComponent;
}

void ALylatGenericRail::SpawnActorOnRail()
{
	if (ActorToSpawn)
	{
		if (SplineComponent)
		{
			spawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, this->SplineComponent->GetTransformAtDistanceAlongSpline(0, ESplineCoordinateSpace::World));
			UpdateActorTransform(0);	//Start of the rail

			if (!spawnedActor)
			{
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, this->GetName() + TEXT(" : Rail : Actor not correctly spawned ()"));
			}
		}
		else
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, this->GetName() + TEXT(" : Rail : Spline component is wrong (not created ?)"));
		}
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, this->GetName() + TEXT(" : Rail : Actor to spawn not set"));
	}
}

void ALylatGenericRail::UpdateActorTransform(const float& Time)
{
	if (this->spawnedActor && this->SplineComponent)
		this->spawnedActor->SetActorTransform(this->SplineComponent->GetTransformAtDistanceAlongSpline(Time, ESplineCoordinateSpace::World));
}
