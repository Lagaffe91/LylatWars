// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LylatEntity.h"
#include "LylatEnemy.generated.h"

UCLASS()
class ALylatEnemy : public ALylatEntity
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALylatEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Lylat Enemy|Mouvement")
		void Mouvement(float DeltaTime); //Can define mouvement in bleuprint, Use Mouvement_Implementation otherwise
	virtual void Mouvement_Implementation(float DeltaTime) {};
};
