// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatGameMode.h"

//TODO(victor): temporary
#include "DebugString.h"

ALylatGameMode::ALylatGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void ALylatGameMode::AddScore(int value)
{
	Score += value;
	//TODO(victor): temporary
	Debug("Score = %d", Score);
}
