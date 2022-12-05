// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatEventTrigger.h"

#include "Components/BoxComponent.h"
#include "LylatPlayerPawn.h"
#include "DebugString.h"

// Sets default values
ALylatEventTrigger::ALylatEventTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EntitySceneComponent"));
	}

	EventHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Entity Hitbox"));
	EventHitbox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALylatEventTrigger::BeginPlay()
{
	Super::BeginPlay();
	Debug("BeginPlay");
	
	EventHitbox->OnComponentBeginOverlap.AddDynamic(this, &ALylatEventTrigger::HitboxBeginOverlap);
}

// Called every frame
void ALylatEventTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALylatEventTrigger::HitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALylatPlayerPawn* Player = Cast<ALylatPlayerPawn>(OtherActor);
	
	if(Player && !EventIsTriggered)
	{ 
		this->EventIsTriggered = true;
		ResolveEvent();
	}
}

void ALylatEventTrigger::ResolveEvent_Implementation()
{
	Debug("Event !");
}

