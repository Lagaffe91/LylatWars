// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatBoss.h"


// Sets default values
ALylatBoss::ALylatBoss()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Lives = 5.0f;
	IsDead = false;


	USceneComponent* Boss = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));


	BossMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BossMesh"));
	BossMesh->SetRelativeLocationAndRotation(BossPosition, FQuat::MakeFromEuler(BossRotation));
	BossMesh->SetupAttachment(Boss);

}

// Called when the game starts or when spawned
void ALylatBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALylatBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsDead)
	{
		BasicMovement(DeltaTime);
	}
}

// Called to bind functionality to input
void ALylatBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALylatBoss::BasicMovement(float deltaTime)
{

	BossRotation.Z += FMath::Cos(deltaTime) / 2;
	BossRotation.X -= FMath::Sin(deltaTime) / 4;


	BossMesh->SetRelativeLocationAndRotation(BossPosition + GetActorLocation(), FQuat::MakeFromEuler(BossRotation));

}



