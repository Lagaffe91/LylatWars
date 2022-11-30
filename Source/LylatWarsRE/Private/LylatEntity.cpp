// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatEntity.h"

#include "DebugString.h"
#include "Components/BoxComponent.h"

// Sets default values
ALylatEntity::ALylatEntity()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EntityLife = EntityMaxLife;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("EntitySceneComponent"));
	}

	EntityMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EntityMesh"));
	EntityMesh->SetupAttachment(RootComponent);

	BulletSpawnPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("BulletSpawn"));
	BulletSpawnPosition->SetupAttachment(EntityMesh);
	EntityHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("Entity Hitbox"));
	EntityHitbox->SetupAttachment(EntityMesh);
	EntityHitbox->SetGenerateOverlapEvents(true);
	EntityHitbox->OnComponentBeginOverlap.AddDynamic(this, &ALylatEntity::HitboxBeginOverlap);
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

void ALylatEntity::HitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Debug("Entity is colliding",0);
    //TODO(victor):move this inside enemy death function
	ALylatGameMode *GameMode = dynamic_cast<ALylatGameMode*>(UGameplayStatics::GetGameMode(GetWorld()));
	GameMode->AddScore(10);
}