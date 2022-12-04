// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatMikuEnemy.h"

#include "LylatPlayerPawn.h"
#include "DebugString.h"

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

void ALylatMikuEnemy::Animate_Implementation(float DeltaTime)
{
	FQuat NewRotation = this->EntityMesh->GetComponentQuat() * FQuat(FVector(0, 0, 1), DeltaTime * AnimationSpeed);
	this->EntityMesh->SetWorldRotation(NewRotation, false, nullptr, ETeleportType::None);
}

void ALylatMikuEnemy::ResetShotTimer()
{
	this->MikuShotTimer = this->MikuShotCooldown + FMath::RandRange(0.f, this->MikuRandomCooldown);
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
	ALylatNormalBullet* Projectile = GetWorld()->SpawnActor<ALylatNormalBullet>(BulletType, Location, Rotation, SpawnParams);
	
	if (Projectile)
	{
		//Set the projectile's initial trajectory.
		FVector LaunchDirection = this->PlayerReference->EntityMesh->GetComponentLocation() - this->EntityMesh->GetComponentLocation();
		LaunchDirection.Normalize();
		Projectile->FireInDirection(LaunchDirection, this);
	}
}

int ALylatMikuEnemy::GetScoreAmount()
{
	return 300;
}
