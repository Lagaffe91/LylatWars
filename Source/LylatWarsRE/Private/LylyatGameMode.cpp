// Fill out your copyright notice in the Description page of Project Settings.


#include "LylyatGameMode.h"

ALylyatGameMode::ALylyatGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void ALylyatGameMode::AddScore(int value)
{
	Score += value;
}
