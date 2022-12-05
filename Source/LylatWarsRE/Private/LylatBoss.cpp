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
#if 0
	IsAttacking = false;
#endif

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


	if (EntityLife > 0.0f)
	{
		BossShoot();

		if (!(FireCount % FireRate))
			Fire();
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
#endif

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FIREEEEEEE !!")));
}



void ALylatBoss::TakeBulletDamage(ALylatNormalBullet* bullet)
{
#if 0
	if (bullet->isPlayerSpawned)
	{
		EntityLife--;
	}

	if (EntityLife <= 0.0f)
		DestroyEntity();
#endif

	FVector Scale = EntityMesh->GetComponentScale();

	Scale -= FVector(0.05f, 0.05f, 0.05f);


	if(EntityMesh->GetComponentScale().GetAbsMin() >= 0.1f)
		this->EntityMesh->SetWorldScale3D(Scale);

	ALylatEntity::TakeBulletDamage(bullet);

}


void ALylatBoss::BossShoot()
{
	if (BulletCooldown <= 0.0f)
	{

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		float distanceToTarget = FVector::DistSquared(PlayerReference->PlayerPosition, BossPosition);
		if (distanceToTarget <= AttackRange * AttackRange)
		{
			FVector Location = BulletSpawnPosition->GetComponentLocation();
			FRotator Rotation = BossRotation.Rotation();
			ALylatNormalBullet* Projectile = GetWorld()->SpawnActor<ALylatNormalBullet>(ALylatNormalBullet::StaticClass(), Location, Rotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = PlayerReference->EntityMesh->GetComponentLocation() - this->EntityMesh->GetComponentLocation();
				LaunchDirection.Normalize();

				if (BossBulletMesh)
					Projectile->SetBulletMesh(BossBulletMesh);
				Projectile->FireInDirection(LaunchDirection, this);
				FireCount++;
			}

			BulletCooldown = 0.6f;
		}

	}
}