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

	if (railStartDelay > 0)
	{
		FTimerHandle _;
		GetWorldTimerManager().SetTimer(_, this, &ALylatGenericRail::SpawnActorsOnRail, railStartDelay, false);
	}
	else
	{
		this->SpawnActorsOnRail();
	}
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
		
		if(RailShouldLoop())	//May cause problem with loop on rail -> ugly fix : Use end rail event to jump from one classic rail to a looped one....
		{
			if(SplineComponent->IsClosedLoop())
			{ 
				RailLoop();
			}
			else
			{
				this->RailIsOver = true;
				this->RailEnded();
			}
		}

		this->UpdateAllActorsTransform(railTime);
	}
}

void ALylatGenericRail::JoinRail(TSubclassOf<ALylatEntity> Actor)
{
	if (Actor)
	{
		ActorsOnRail.Add(Actor.GetDefaultObject());

		ComputeEnityMeshTransform(Actor.GetDefaultObject());
	}
}

void ALylatGenericRail::JoinRailArray(TArray<ALylatEntity*> Actors)
{
	this->ActorsOnRail += Actors;
	
	//Compute new mesh location
	for (ALylatEntity* Entity : Actors)
	{
		ComputeEnityMeshTransform(Entity);
	}
}

void ALylatGenericRail::SetRailSpeed(const float& NewSpeed)
{
	this->railSpeed = NewSpeed;
}

void ALylatGenericRail::RailEnded_Implementation()
{
	this->DestroyAllActors();
}

bool ALylatGenericRail::RailShouldLoop()
{
	return railTime > SplineComponent->GetSplineLength();
}

void ALylatGenericRail::DestroyAllActors()
{
	for (ALylatEntity* entity : ActorsOnRail)
	{
		entity->Destroy();
	}
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

void ALylatGenericRail::ComputeEnityMeshTransform(ALylatEntity* Entity)
{
	if(Entity)
	{ 
		//FVector meshPosition = Entity->EntityMesh->GetComponentLocation();
		FTransform meshTransform = Entity->EntityMesh->GetComponentTransform();

		this->UpdateActorTransform(Entity, railTime);
		
		Entity->EntityMesh->SetWorldTransform(meshTransform);
	}
	else
	{
		DebugError("ComputeEnityMeshTransform : Entity is null", 0);
	}
}

void ALylatGenericRail::SpawnActorsOnRail()
{
	if (!SpawnActor)
		return;

	if (SplineComponent)
	{
		for (TSubclassOf<ALylatEntity> actor : ActorsToSpawn)
		{
			ALylatEntity*actorPtr = GetWorld()->SpawnActor<ALylatEntity>(actor, this->SplineComponent->GetTransformAtDistanceAlongSpline(0, ESplineCoordinateSpace::World));
			
			if (!actorPtr)
			{
				if (GEngine)
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, this->GetName() + TEXT(" : Rail : Actor not correctly spawned"));
			}
			else
			{
				ActorsOnRail.Add(actorPtr);
				Debug("Actord spawned :%s " , *actorPtr->GetName());
			}
		}
	}
	else
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, this->GetName() + TEXT(" : Rail : Spline component is wrong (not created ?)"));
	}
}

void ALylatGenericRail::UpdateActorTransform(TSubclassOf<ALylatEntity> Actor, const float& Time)
{
	UpdateActorTransform(Actor.GetDefaultObject(), Time);
}

void ALylatGenericRail::UpdateActorTransform(ALylatEntity* Actor, const float& Time)
{
	if (Actor && this->SplineComponent)
	{
		FTransform NewTranform = this->SplineComponent->GetTransformAtDistanceAlongSpline(Time, ESplineCoordinateSpace::World);
		Actor->SetActorTransform(NewTranform);
	}
	else
	{
		DebugError("Failed to update transform", 0);
	}
}

void ALylatGenericRail::UpdateAllActorsTransform(const float& Time)
{
	for (ALylatEntity* Actor : ActorsOnRail)
	{
		UpdateActorTransform(Actor, Time);
	}
}