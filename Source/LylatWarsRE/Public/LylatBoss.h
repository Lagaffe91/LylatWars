// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "LylatNormalBullet.h"
#include "LylatWeakPoint.h"

#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

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
	float Speed = 500.0f;
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* BossMesh;

#if 1
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* BossLefGun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* BossRightGun;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		FVector LeftGunPosition = FVector(310.0F, -260, 170.0F);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		FVector RightGunPosition = FVector(310.0f,260,170.0f);

#endif

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


	UPROPERTY(EditDefaultsOnly, Category = "FireParticle")
		UParticleSystem* FireParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		 bool CanFire;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		bool IsAttacking;


	//NOTE(o.lunada): Maybe we should do with an AI ..thinking on that
	void Fire();
	void Attack();
		

protected:
	float BulletCooldown;



};
