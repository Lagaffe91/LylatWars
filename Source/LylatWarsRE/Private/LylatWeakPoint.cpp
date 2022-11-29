// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatWeakPoint.h"

// Sets default values
ALylatWeakPoint::ALylatWeakPoint()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* WeakPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));


	PointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeakMesh"));
	PointMesh->SetRelativeLocationAndRotation(PointPosition, FQuat::MakeFromEuler(PointRotation));
	PointMesh->SetupAttachment(WeakPoint);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->BodyInstance.SetCollisionProfileName("OverlapAll");
	CollisionBox->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0), FRotator(0.0f, 0.0f, 0.0f));
	CollisionBox->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	CollisionBox->SetupAttachment(WeakPoint);

}

// Called when the game starts or when spawned
void ALylatWeakPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALylatWeakPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALylatWeakPoint::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

