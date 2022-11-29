// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatEntity.h"

// Sets default values
ALylatEntity::ALylatEntity()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* base = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	EntityMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntityMesh"));
	EntityMesh->SetupAttachment(base);
}

// Called when the game starts or when spawned
void ALylatEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALylatEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALylatEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

