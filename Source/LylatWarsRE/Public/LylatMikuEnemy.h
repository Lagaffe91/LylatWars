// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LylatEnemy.h"

#include "LylatMikuEnemy.generated.h"

/**
 * 
 */
UCLASS()
class LYLATWARSRE_API ALylatMikuEnemy : public ALylatEnemy
{
	GENERATED_BODY()

public :
	ALylatMikuEnemy();

public :

	/**Cooldown between two shots (in seconds)*/
	UPROPERTY(Category = "Miku", EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
		float MikuShotCooldown = 5;
	/**Random Cooldown added between two shots (in seconds)*/
	UPROPERTY(Category = "Miku", EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
		float MikuRandomCooldown = 2;

	UPROPERTY(Category = "Miku", VisibleInstanceOnly, BlueprintReadOnly)
		float MikuShotTimer = 5;

public :
	void Behaviour_Implementation(float DeltaTime)	override;

	void Animate_Implementation(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Miku")
		void ResetShotTimer();

	UFUNCTION(BlueprintCallable, Category = "Miku")
		void SetCooldown(const float& NewCooldown);

	virtual void ShootBullet() override;
};
