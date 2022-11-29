// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "LylatNormalBullet.h"
#include "LylatWeakPoint.h"

#include "LylatBoss.generated.h"


UCLASS()
class LYLATWARSRE_API ALylatBoss : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALylatBoss();
	void BasicMovement(float deltaTime);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float Speed = 500.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* BossMesh;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
		int Lives;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
		bool IsDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		FVector BossPosition = FVector(0, 0, 0);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		FVector BossRotation = FVector(0, 0, 0);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		TArray<ALylatWeakPoint*> BossWeakPoints;

private:
	float BulletCooldown;



};
