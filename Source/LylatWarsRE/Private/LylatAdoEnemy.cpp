// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatAdoEnemy.h"

void ALylatAdoEnemy::Animate_Implementation(float DeltaTime)
{
	FQuat NewRotation = this->EntityMesh->GetComponentQuat() * FQuat(FVector(0,1,0), DeltaTime*AnimationSpeed);
	this->EntityMesh->SetWorldRotation(NewRotation);
}

void ALylatAdoEnemy::Behaviour_Implementation(float DeltaTime)
{
	//Do nothing ?
}

int ALylatAdoEnemy::GetScoreAmount()
{
	return 100;
}