// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatEntity.h"

#include "DebugString.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "LylatNormalBullet.h"
#include "LylatPlayerPawn.h"
#include "LylatGameInstance.h"

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
	auto comps = GetComponents();
	for (UActorComponent* element : comps)
	{
		UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(element);
		if (mesh)
		{
			meshes.Add(mesh);
		}
	}
}

// Called every frame
void ALylatEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (EntityCurrentInvulneability > 0.0f)
	{
		EntityCurrentInvulneability -= DeltaTime;
		if (EntityCurrentInvulneability <= 0.0f)
		{
			EndDamageEvent();
		}
	}
}

// Called to bind functionality to input
void ALylatEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALylatEntity::HitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this || EntityLife <= 0 || EntityCurrentInvulneability > 0.0f) return;
	ALylatNormalBullet* bullet = Cast<ALylatNormalBullet>(OtherActor);
	if (bullet)
	{
		return;
	}
	else
	{
		TakeEntityDamage(OtherActor);
		EntityCurrentInvulneability = EntityInvulneability;
	}
}

void ALylatEntity::TakeBulletDamage(ALylatNormalBullet* bullet)
{
	if (!bullet->isPlayerSpawned) return;
	//Debug("Touched bullet", 0);
	TakeDamageEvent();
	EntityLife--;
	if (EntityLife <= 0)
	{
		DestroyEntity();
	}
}

void ALylatEntity::TakeEntityDamage(AActor* entity)
{
	TakeDamageEvent();
	EntityLife--;
	if (EntityLife <= 0)
	{
		DestroyEntity();
	}
}

void ALylatEntity::DestroyEntity(bool addScore)
{
	if (addScore)
	{
		ULylatGameInstance* instance = Cast<ULylatGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (instance)
		{
			instance->Score += EntityScoreValue;
		}
		else
		{
			DebugError("Invalid game instance, please assign ALylatGameInstance inside project settings", 0);
		}
	}
	this->OnDestroy();
	Destroy();
}

void ALylatEntity::RailEnded_Implementation()
{
	this->DestroyEntity(false);
}

void ALylatEntity::TakeDamageEvent_Implementation()
{
	for (UStaticMeshComponent* mesh : meshes)
	{
		for (int32 i = 0; i < mesh->GetNumMaterials(); i++)
		{
			mesh->OverrideMaterials.Add(DamageMaterial);
		}
		mesh->MarkRenderStateDirty();
	}
}

void ALylatEntity::EndDamageEvent_Implementation()
{
	for (UStaticMeshComponent* mesh : meshes)
	{
		mesh->OverrideMaterials.Empty();
		mesh->MarkRenderStateDirty();
	}
}
