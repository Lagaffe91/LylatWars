// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LylatEntity.generated.h"

UCLASS()
class ALylatEntity : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALylatEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = "Lylat Enity", VisibleDefaultsOnly, BlueprintReadOnly)
		class UStaticMeshComponent* EntityMesh;

};
