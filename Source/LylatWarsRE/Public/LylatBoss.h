// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
//#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "LylatWeakPoint.h"

#include "Particles/ParticleSystem.h"
#include "Engine/TriggerBox.h"

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
	float BulletCooldown;
	int FireCount;

private:
	bool ShieldDesactivated = false;
	bool BombTurn = false;
	bool bMoveEight = false;
	float eightShapeTimer = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = "Boss Bullet", VisibleAnywhere, BlueprintReadOnly)
		class UArrowComponent* Bomb1SpawnPosition;
	UPROPERTY(Category = "Boss Bullet", VisibleAnywhere, BlueprintReadOnly)
		class UArrowComponent* Bomb2SpawnPosition;

	UPROPERTY(Category = "Boss Bullet Mesh", EditDefaultsOnly)
		UStaticMesh* BossBulletMesh = nullptr;

	UPROPERTY(Category = "Boss Bullet Mesh", EditDefaultsOnly)
		UStaticMesh* BossBombMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		FVector BossPosition = FVector(0, 0, 0);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		FVector BossRotation = FVector(0, 0, 0);


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		TArray<ALylatWeakPoint*> BossWeakPoints;

	UPROPERTY(Category = "Boss Aura Material", EditAnywhere, BlueprintReadOnly)
		class UMaterialInterface* BossAuraMaterial;


	UPROPERTY(EditDefaultsOnly, Category = "FireParticle")
		UParticleSystem* FireParticle;

	UPROPERTY(Category = "Attack Range",EditAnywhere, BlueprintReadOnly)
		float AttackRange = 1000.0f;

	UPROPERTY(Category = "Attack Range", EditAnywhere, BlueprintReadOnly)
		int BossAuraRate = 20;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Range")
		int FireRate = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Range")
		float BulletSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss Scale Damage")
		float ScaleDamage = 0.05f;

	void Fire();
	
	virtual void TakeBulletDamage(ALylatNormalBullet* bullet) override;
	void ActivateBossAura();
	void DesactivateBossAura();
protected:
	void BossShoot();
private:
	void EightMovement();

};
