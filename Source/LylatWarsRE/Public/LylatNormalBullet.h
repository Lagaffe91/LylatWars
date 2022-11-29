// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "LylatNormalBullet.generated.h"

UCLASS()
class LYLATWARSRE_API ALylatNormalBullet : public AActor
{
	GENERATED_BODY()

public:
	UProjectileMovementComponent *BulletMovement;
	UStaticMeshComponent         *SphereMesh;
	USphereComponent             *CollisionComponent;
public:	
	// Sets default values for this actor's properties
	ALylatNormalBullet(const FObjectInitializer& ObjectInitializer);

	void FireInDirection(const FVector& ShootDirection);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
