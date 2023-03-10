// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
//#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "LylatWeakPoint.h"

#include "Particles/ParticleSystem.h"
#include "Engine/TriggerBox.h"
#include "LylatBombBullet.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category = "Boss Difficulty", EditDefaultsOnly)
		int JeffLives = 5;
	UPROPERTY(Category = "Boss Bullet", VisibleAnywhere, BlueprintReadOnly)
		class UArrowComponent* Bomb1SpawnPosition;
	UPROPERTY(Category = "Boss Bullet", VisibleAnywhere, BlueprintReadOnly)
		class UArrowComponent* Bomb2SpawnPosition;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		FVector BossPosition = FVector(0, 0, 0);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		FVector BossRotation = FVector(0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float ShapeScale = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float ShapeSpeed = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		TArray<ALylatWeakPoint*> BossWeakPoints;

	UPROPERTY(Category = "Boss Aura Material", EditAnywhere, BlueprintReadOnly)
		class UMaterialInterface* BossAuraMaterial;

	UPROPERTY(Category = "Lylat Boss Bomb|Weapons", EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ALylatBombBullet> BombBulletType;


	UPROPERTY(EditDefaultsOnly, Category = "FireParticle")
		UParticleSystem* FireParticle;

	UPROPERTY(Category = "Attack Range",EditAnywhere, BlueprintReadOnly)
		float AttackRange = 1000.0f;

	UPROPERTY(Category = "Attack Range", EditAnywhere, BlueprintReadOnly)
		int BossAuraRate = 20;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Range")
		int FireRate = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Range")
		int BomRate = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attack Range")
		float BulletSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss Scale Damage")
		float ScaleDamage = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss")
		float BossBulletCooldown = 0.6f;

	
	virtual void TakeBulletDamage(ALylatNormalBullet* bullet, int amount = 1) override;
	void ActivateBossAura();
	void DesactivateBossAura();
protected:
	void BossShoot();
private:
	void EightMovement();

};
