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
		this->UpdateEntitySpawning(DeltaTime);
		this->UpdateAllActorsTransform(DeltaTime);
	}
}

void ALylatGenericRail::JoinRail(TSubclassOf<ALylatEntity> Actor)
{
	if (Actor)
	{
		ActorsOnRail.Add(Actor.GetDefaultObject());
		Actor.GetDefaultObject()->EntityIsOnARail = true;
		Actor.GetDefaultObject()->EntityRailDistance = 0;
		ComputeEnityMeshTransform(Actor.GetDefaultObject());
	}
}

void ALylatGenericRail::JoinRailArray(TArray<ALylatEntity*> Actors)
{
	this->ActorsOnRail += Actors;

	for (ALylatEntity* Entity : Actors)
	{
		Entity->EntityRailDistance = 0;
		Entity->EntityIsOnARail = true;
		ComputeEnityMeshTransform(Entity);
	}
}

void ALylatGenericRail::SetRailSpeed(const float& NewSpeed)
{
	this->railSpeed = NewSpeed;
}

bool ALylatGenericRail::RailShouldLoop(ALylatEntity* Entity)
{
	return Entity->EntityRailDistance > SplineComponent->GetSplineLength();
}

void ALylatGenericRail::DestroyAllActors()
{
	for (ALylatEntity* entity : ActorsOnRail)
	{
		entity->DestroyEntity(false);
	}
}

void ALylatGenericRail::RailLoop(ALylatEntity* Entity)
{
	Entity->EntityRailDistance /= SplineComponent->GetSplineLength();
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
		FTransform meshTransform = Entity->EntityMesh->GetComponentTransform();

		this->UpdateActorTransform(Entity, 0);
		
		Entity->EntityMesh->SetWorldTransform(meshTransform);
	}
	else
	{
		DebugError("ComputeEnityMeshTransform : Entity is null", 0);
	}
}

void ALylatGenericRail::SpawnActorsOnRail()
{	
	DebugError("ALylatGenericRail::SpawnActorsOnRail() : !! DEPRECATED FUNCTION !!", 0);
}

void ALylatGenericRail::ComputeRailDistance(float DeltaTime, ALylatEntity* Entity)
{
	Entity->EntityRailDistance += DeltaTime * speedMultiplier * railSpeed;

	if (RailShouldLoop(Entity))
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

void ALylatGenericRail::UpdateActorTransform(TSubclassOf<ALylatEntity> Actor, const float& DeltaTime)
{
	UpdateActorTransform(Actor.GetDefaultObject(), DeltaTime);
}

void ALylatGenericRail::UpdateActorTransform(ALylatEntity* Entity, const float& DeltaTime)
{
	if (Entity && this->SplineComponent)
	{
		this->ComputeRailDistance(DeltaTime, Entity);
		FTransform NewTranform = this->SplineComponent->GetTransformAtDistanceAlongSpline(Entity->EntityRailDistance, ESplineCoordinateSpace::World);
		Entity->SetActorTransform(NewTranform);
	}
	else
	{
		DebugError("Failed to update transform (no spline/bad entity)", 0);
	}
}

void ALylatGenericRail::UpdateAllActorsTransform(const float& DeltaTime)
{
	for (ALylatEntity* Actor : ActorsOnRail)
	{
		if (Actor)
		{
			UpdateActorTransform(Actor, DeltaTime);
		}
		else
		{
			ActorsOnRail.Remove(Actor);
		}
	}
}

void ALylatGenericRail::UpdateEntitySpawning(float DeltaTime)
{
	if (this->ShouldSpawn())
	{
		this->SpawnTimer += DeltaTime;

		if (this->SpawnTimer >= SpawnDelay)
		{
			this->SpawnNextEntity();
			this->SpawnTimer = 0;
		}
	}
}

bool ALylatGenericRail::ShouldSpawn()
{
	return this->ActorsToSpawn.Num() > 0 && (this->InifiniteSpawn || !ActorsAreSpawned);
}

void ALylatGenericRail::SpawnNextEntity()
{
	if (!this->ActorsToSpawn.IsValidIndex(this->NextEntityIndex))
	{
		Debug("Bad index : index : %i", this->NextEntityIndex);
		return;
	}
	TSubclassOf<ALylatEntity> SubClassEntity = this->ActorsToSpawn[this->NextEntityIndex];

	ALylatEntity* Entity = nullptr;
	if (SubClassEntity)
	{
		Entity = SubClassEntity.GetDefaultObject();
	}
	else
	{
		DebugError("Internal error : Cant spawn entity (bad index)",0);
		return;
	}
	
	this->NextEntityIndex++;

	if (!this->ActorsToSpawn.IsValidIndex(this->NextEntityIndex))
	{
		this->NextEntityIndex = 0;
		ActorsAreSpawned = true;	//First loop of the list
	}

	this->SpawnEntity(Entity);
}

void ALylatGenericRail::SpawnEntity(ALylatEntity* Entity)
{
	if (!Entity || !SplineComponent)
	{
		DebugError("Failed to spawn entity (no spline/bad entity)", 0);
		return;
	}

	ALylatEntity* EntityPtr = GetWorld()->SpawnActor<ALylatEntity>(Entity->GetClass(), this->SplineComponent->GetTransformAtDistanceAlongSpline(0, ESplineCoordinateSpace::World));

	if (!EntityPtr)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, this->GetName() + TEXT(" : Rail : Actor not correctly spawned"));
	}
	else
	{
		this->ActorsOnRail.Add(EntityPtr);
		Debug("Actord spawned :%s ", *EntityPtr->GetName());
	}
}