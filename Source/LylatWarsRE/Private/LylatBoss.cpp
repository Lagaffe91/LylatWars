// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatBoss.h"
#include "LylatWeakPoint.h"
#include "Kismet/GameplayStatics.h"	

#include "LylatPlayerPawn.h"
#include "LylatNormalBullet.h"
#include "LylatWarsRE/Public/LylatHomingBullet.h"

// Sets default values
ALylatBoss::ALylatBoss()
{
	PrimaryActorTick.bCanEverTick = true;

	Bomb1SpawnPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Bomb1Spawn"));
	Bomb1SpawnPosition->SetupAttachment(EntityMesh);

	Bomb2SpawnPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Bomb2Spawn"));
	Bomb2SpawnPosition->SetupAttachment(EntityMesh);

	EntityLife = 1;
	BulletCooldown = 0.0f;
	FireCount = 0;
}

// Called when the game starts or when spawned
void ALylatBoss::BeginPlay()
{
	Super::BeginPlay();
	ActivateBossAura();
	bMoveEight = true;

	//Give jeff turrets 5 life
	TArray<AActor *> childActors;
	GetAllChildActors(childActors);
	for (auto child : childActors)
	{
		ALylatEntity *current = Cast<ALylatEntity>(child);
		current->EntityLife = JeffLives;
	}
}


void ALylatBoss::EightMovement()
{
	FVector Location = {0, 0, 0};

	float worldTime = GetWorld()->GetTimeSeconds() * ShapeSpeed;
	Location.Y = cos(worldTime) * ShapeScale;
	Location.Z = (sin(worldTime * 2) / 2) * ShapeScale;

	FVector interpolation = FMath::Lerp(Location, EntityMesh->GetRelativeLocation(), 0.99f);
	EntityMesh->SetRelativeLocation(interpolation);
}

// Called every frame
void ALylatBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BulletCooldown -= DeltaTime;

	if (EntityLife <= 0)
		Destroy();
	else if (BulletCooldown <= 0.0f)
		BossShoot();

	if (bMoveEight)
		EightMovement();
}

// Called to bind functionality to input
void ALylatBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ALylatBoss::BasicMovement(float deltaTime)
{
	EntityMesh->SetRelativeLocationAndRotation(BossPosition, FQuat::MakeFromEuler(BossRotation));
}


void ALylatBoss::TakeBulletDamage(ALylatNormalBullet* bullet, int amount)
{
	TArray<AActor *> childActors;
	GetAllChildActors(childActors);

	for (auto child : childActors)
	{
		if (!child->IsActorBeingDestroyed())
		{
			ActivateBossAura();
			return;
		}
	}
	if (!ShieldDesactivated)
	{
		DesactivateBossAura();
		ShieldDesactivated = true;
	}
	ALylatEnemy::TakeBulletDamage(bullet, amount);
}


void ALylatBoss::BossShoot()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	BossPosition = GetActorLocation();
	float distanceToTarget = FVector::DistSquared(PlayerReference->GetActorLocation(), BossPosition);
	if (distanceToTarget <= AttackRange * AttackRange)
	{
		FVector Location = BulletSpawnPosition->GetComponentLocation();
		bool bomb = false;
		if (!(FireCount % FireRate))
		{
			bomb = true;
			if (BombTurn)
			{
				Location = Bomb1SpawnPosition->GetComponentLocation();
				BombTurn = !BombTurn;
			}
			else
			{
				Location = Bomb2SpawnPosition->GetComponentLocation();
				BombTurn = !BombTurn;
			}
		}
		FRotator Rotation = BossRotation.Rotation();
		ALylatNormalBullet* Projectile;
		if (bomb) Projectile = GetWorld()->SpawnActor<ALylatNormalBullet>(BombBulletType, Location, Rotation, SpawnParams);
		else Projectile = GetWorld()->SpawnActor<ALylatNormalBullet>(BulletType, Location, Rotation, SpawnParams);

		if (Projectile)
		{
			FVector LaunchDirection = PlayerReference->EntityMesh->GetComponentLocation() - Location;
			LaunchDirection.Normalize();

			Projectile->SetInitialSpeed(BulletSpeed);
			Projectile->FireInDirection(LaunchDirection, this);
			PlayLaserSound();
			FireCount++;
		}
	}
	BulletCooldown = BossBulletCooldown;
}


void ALylatBoss::ActivateBossAura()
{
	for (UStaticMeshComponent* mesh : meshes)
	{
		for (int32 i = 0; i < mesh->GetNumMaterials(); i++)
		{
			mesh->OverrideMaterials.Add(BossAuraMaterial);
		}
		mesh->MarkRenderStateDirty();
	}
}

void ALylatBoss::DesactivateBossAura()
{
	for (UStaticMeshComponent* mesh : meshes)
	{
		mesh->OverrideMaterials.Empty();
		mesh->MarkRenderStateDirty();
	}
}