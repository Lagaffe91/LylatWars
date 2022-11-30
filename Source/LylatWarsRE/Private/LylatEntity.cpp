// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatEntity.h"

#include "DebugString.h"
#include "Components/BoxComponent.h"
#include "LylatNormalBullet.h"
#include "LylatPlayerPawn.h"

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
}

// Called when the game starts or when spawned
void ALylatEntity::BeginPlay()
{
	Super::BeginPlay();
	EntityHitbox->SetGenerateOverlapEvents(true);
	EntityHitbox->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // We want overlaps.
	EntityHitbox->SetCollisionResponseToAllChannels(ECR_Overlap);
	EntityHitbox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALylatEntity::HitboxBeginOverlap);
	EntityLife = EntityMaxLife;
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
	if (OtherActor == this || EntityLife <= 0) return;
	ALylatNormalBullet* bullet = Cast<ALylatNormalBullet>(OtherActor);
	if (bullet)
	{
		return;
	}
	else
	{
		//Debug("Touched actor %s", *OtherActor->GetName());
		TakeEntityDamage(OtherActor);
	}
}

void ALylatEntity::TakeBulletDamage(ALylatNormalBullet* bullet)
{
	if (!bullet->isPlayerSpawned) return;
	//Debug("Touched bullet", 0);
	EntityLife--;
	if (EntityLife <= 0)
	{
		DestroyEntity();
	}
}

void ALylatEntity::TakeEntityDamage(AActor* entity)
{
}

void ALylatEntity::DestroyEntity()
{
	Destroy();
}
