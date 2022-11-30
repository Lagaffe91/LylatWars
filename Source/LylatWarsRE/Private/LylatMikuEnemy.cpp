// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatMikuEnemy.h"

ALylatMikuEnemy::ALylatMikuEnemy()
{
	ResetShotTimer();
}

void ALylatMikuEnemy::Behaviour_Implementation(float DeltaTime)
{
	if (this->MikuShotTimer > 0)
	{
		this->MikuShotTimer -= DeltaTime;
	}
	else
	{
		this->ResetShotTimer();
		this->ShootBullet();
	}
}

void ALylatMikuEnemy::ResetShotTimer()
{
	this->MikuShotTimer = this->MikuShotCooldown;
}

void ALylatMikuEnemy::SetCooldown(const float& NewCooldown)
{
	if(NewCooldown > 0)
	{ 
		this->MikuShotCooldown = NewCooldown;
	}
}

void ALylatMikuEnemy::ShootBullet()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector Location = EntityMesh->GetComponentLocation();
	FRotator Rotation = this->EntityMesh->GetComponentRotation();
	ALylatNormalBullet* Projectile = GetWorld()->SpawnActor<ALylatNormalBullet>(ALylatNormalBullet::StaticClass(), Location, Rotation, SpawnParams);
	if (Projectile)
	{
		// Set the projectile's initial trajectory.
		//FVector LaunchDirection = this->GetWorld();
		//Projectile->FireInDirection(LaunchDirection);
	}
}

int ALylatMikuEnemy::GetScoreAmount()
{
	return 100;
}
