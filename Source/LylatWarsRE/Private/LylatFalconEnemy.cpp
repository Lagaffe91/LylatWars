// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatFalconEnemy.h"

#include "DebugString.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"

void ALylatFalconEnemy::Behaviour_Implementation(float DeltaTime)
{
	if (!this->isRolling && this->FalconRollTimer > 0)
	{
		this->FalconRollTimer -= DeltaTime;
	}
	else
	{
		this->isRolling = true;
		EntityHitbox->SetActive(false);
	}
}

void ALylatFalconEnemy::Animate_Implementation(float DeltaTime)
{
	if (this->isRolling)
		DoBarrelRoll(DeltaTime);
}

void ALylatFalconEnemy::DoBarrelRoll(float DeltaTime)
{
	if (this->AnimationTimer > this->AnimationDuration / this->AnimationSpeed) //Real duration
	{
		this->isRolling = false;
		this->ResetRollCooldown();
	}
	else
	{
		this->AnimationTimer += DeltaTime;

		FVector rotation = this->EntityMesh->GetRelativeRotation().Euler();
		rotation.X = FMath::Lerp(0.0f, 360.0f, this->AnimationTimer / (this->AnimationDuration / this->AnimationSpeed));
		rotation.X = FMath::Fmod(rotation.X, 360.0f);

		if (rotation.X < -180.0f) rotation.X += 360.0f;
		if (rotation.X > 180.0f) rotation.X -= 360.0f;

		this->EntityMesh->SetRelativeRotation(FQuat::MakeFromEuler(rotation));
	}
}

void ALylatFalconEnemy::ResetRollCooldown()
{
	EntityHitbox->SetActive(true);
	this->AnimationTimer = 0;
	this->FalconRollTimer = this->FalconRollCooldown + FMath::RandRange(0, this->FalcomRandomCooldown);
}
