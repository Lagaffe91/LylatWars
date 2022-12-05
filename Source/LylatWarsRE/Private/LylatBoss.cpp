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

	BulletCooldown = 0.0f;
	FireCount = 0;
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
	BulletCooldown -= DeltaTime;

	if (EntityLife <= 0)
		Destroy();
	else if (BulletCooldown <= 0.0f)
	{
		BossShoot();
	}
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

void ALylatBoss::Fire()
{

#if 0
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireParticle, this->EntityMesh->GetComponentLocation(), FRotator::ZeroRotator, true);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FIREEEEEEE !!")));
#endif



}

void ALylatBoss::TakeBulletDamage(ALylatNormalBullet* bullet)
{
	TArray<AActor *> childActors;
	GetAllChildActors(childActors);

	for (auto child : childActors)
	{
		if (!child->IsActorBeingDestroyed())
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, child->GetName());
			return;
		}
	}

	if (FireCount % ChanceToTakeDamage)
	{
		DesactivateBossShield();

		FVector Scale = EntityMesh->GetComponentScale();

		Scale -= FVector(ScaleDamage, ScaleDamage, ScaleDamage);

		if(EntityMesh->GetComponentScale().GetAbsMin() >= ScaleDamage  * 2)
			this->EntityMesh->SetWorldScale3D(Scale);


		ALylatEntity::TakeBulletDamage(bullet);

	}
	else
	{
		ActivateBossShield();
	}


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

			if (!(FireCount % FireRate))
			{
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
			ALylatNormalBullet* Projectile = GetWorld()->SpawnActor<ALylatNormalBullet>(ALylatNormalBullet::StaticClass(), Location, Rotation, SpawnParams);

			if (Projectile)
			{
				FVector LaunchDirection = PlayerReference->EntityMesh->GetComponentLocation() - Location;
				LaunchDirection.Normalize();

				if (!(FireCount % FireRate))
				{
					if (BossBombMesh)
						Projectile->SetBulletMesh(BossBombMesh);
					Projectile->FireInDirection(LaunchDirection, this);
				}
				else
				{
					if (BossBulletMesh)
						Projectile->SetBulletMesh(BossBulletMesh);
					Projectile->FireInDirection(LaunchDirection, this);
				}

				FireCount++;
			}
		}
		BulletCooldown = 0.6f;
}

void ALylatBoss::ActivateBossShield()
{
	for (UStaticMeshComponent* mesh : meshes)
	{
		for (int32 i = 0; i < mesh->GetNumMaterials(); i++)
		{
			mesh->SetMaterial(i, BossAuraMaterial);
		}
		mesh->MarkRenderStateDirty();
	}
}

void ALylatBoss::DesactivateBossShield()
{
	for (UStaticMeshComponent* mesh : meshes)
	{
		mesh->OverrideMaterials.Empty();
		mesh->MarkRenderStateDirty();
	}
}


