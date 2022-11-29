// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatHomingBullet.h"

ALylatHomingBullet::ALylatHomingBullet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BulletMovement->bIsHomingProjectile = true;
	BulletMovement->HomingAccelerationMagnitude = 3000.0f;
}

void ALylatHomingBullet::HomingTarget(const AActor *Object)
{
	if(Object)
	{
		BulletMovement->HomingTargetComponent = Object->GetRootComponent();
	}
}
