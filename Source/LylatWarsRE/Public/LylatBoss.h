// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "LylatWeakPoint.h"

#include "Particles/ParticleSystem.h"


#include "LylatEnemy.h"
#include "LylatBoss.generated.h"


UCLASS()
class LYLATWARSRE_API ALylatBoss : public ALylatEnemy
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

	void BossShoot();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = "Boss Bullet Mesh", EditDefaultsOnly)
		UStaticMesh* BossBulletMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		FVector BossPosition = FVector(0, 0, 0);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		FVector BossRotation = FVector(0, 0, 0);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		TArray<ALylatWeakPoint*> BossWeakPoints;


	UPROPERTY(EditDefaultsOnly, Category = "FireParticle")
		UParticleSystem* FireParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		bool IsAttacking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack Range")
		float AttackRange;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack Range")
		int FireRate;


	void Fire();
	
	
	virtual void TakeBulletDamage(ALylatNormalBullet* bullet) override;

protected:
	float BulletCooldown;
	int FireCount;
	



};
