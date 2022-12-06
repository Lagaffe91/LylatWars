// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LylatNormalBullet.h"
#include "LylatBombBullet.generated.h"

/**
 * 
 */
UCLASS()
class LYLATWARSRE_API ALylatBombBullet : public ALylatNormalBullet
{
	GENERATED_BODY()

public:
	ALylatBombBullet(const FObjectInitializer& ObjectInitializer);

	/**Amount of time before the bomb explodes after being fired, in seconds*/
	UPROPERTY(Category = "Lylat Bomb", EditAnywhere, BlueprintReadOnly)
		float BombTimer = 1.5f;

	/**Amount of time is takes for the explosion animation to play, in seconds*/
	UPROPERTY(Category = "Lylat Bomb", EditAnywhere, BlueprintReadOnly)
		float BombExplosionTimer = 1.0f;

	/**Amount of time is takes for the explosion animation to decay, in seconds*/
	UPROPERTY(Category = "Lylat Bomb", EditAnywhere, BlueprintReadOnly)
		float BombDecayTimer = 0.5f;

	/*
	* Will make sure every bullets takes a hit, even if they are outside of the range
	* Note: the bullets takes the hit at the end of the animation (when the explosion is at full radius)
	*/
	UPROPERTY(Category = "Lylat Bomb", EditAnywhere, BlueprintReadOnly)
		bool BombTouchAllBullets = true;

	/*
	* Will make sure every enemies takes a hit, even if they are outside of the range
	* Note: the enemies takes the hit at the end of the animation (when the explosion is at full radius)
	*/
	UPROPERTY(Category = "Lylat Bomb", EditAnywhere, BlueprintReadOnly)
		bool BombTouchAllEnemies = false;

	/*
	* Radius of the explosion (visual only if BombTouchAll is set to true)
	* Note: Will be multiplied to the scale of the SphereMesh component
	*/
	UPROPERTY(Category = "Lylat Bomb", EditAnywhere, BlueprintReadOnly)
		float BombRadius = 3000.0f;

	/*
	* Damage dealt by the bomb (may be applied multiple times if BombTouchAllEnemies is set to true)
	* BTW negative damage may heal entities
	*/
	UPROPERTY(Category = "Lylat Bomb", EditAnywhere, BlueprintReadOnly)
		int BombDamage = 1;

	virtual void Tick(float DeltaTime) override;

	virtual void HitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(Category = "Lylat Bomb", VisibleAnywhere, BlueprintReadOnly)
		float BombCurrentTimer = 0.0f;

	/*
	* Indicate wether or not the bomb is in its second phase of animation (debloating, after killing all the enemies)
	* Note: Can be determined to check if Mario can use this to Bomb-Clip; use at your own risks
	*/
	UPROPERTY(Category = "Lylat Bomb", VisibleAnywhere, BlueprintReadOnly)
		bool IsBloated = false;

	FVector defaultMeshSize;
};
