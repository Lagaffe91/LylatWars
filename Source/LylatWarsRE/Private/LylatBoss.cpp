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

	BombSpawner1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombSpawner1"));
	BombSpawner1->SetupAttachment(EntityMesh);

	BombSpawner2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombSpawner2"));
	BombSpawner2->SetupAttachment(EntityMesh);

	Bomb1SpawnPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Bomb1Spawn"));
	Bomb1SpawnPosition->SetupAttachment(BombSpawner1);

	Bomb2SpawnPosition = CreateDefaultSubobject<UArrowComponent>(TEXT("Bomb2Spawn"));
	Bomb2SpawnPosition->SetupAttachment(BombSpawner2);

	BombSpawnerCollision1 = CreateDefaultSubobject<UBoxComponent>(TEXT("Bomb1SpawnerCollision"));
	BombSpawnerCollision1->SetupAttachment(BombSpawner1);

	BombSpawnerCollision2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Bomb2SpawnerCollision"));
	BombSpawnerCollision2->SetupAttachment(BombSpawner2);

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
	FVector Scale = EntityMesh->GetComponentScale();

	Scale -= FVector(ScaleDamage, ScaleDamage, ScaleDamage);


	if(EntityMesh->GetComponentScale().GetAbsMin() >= ScaleDamage  * 2)
		this->EntityMesh->SetWorldScale3D(Scale);

	ALylatEntity::TakeBulletDamage(bullet);

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
