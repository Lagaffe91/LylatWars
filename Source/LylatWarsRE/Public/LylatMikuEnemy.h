// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LylatEnemy.h"

#include "LylatHomingBullet.h"

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

	UPROPERTY(Category = "Miku", EditAnywhere, BlueprintReadOnly)
		float MikuShotTimer = 5;

public :
	void Behaviour_Implementation(float DeltaTime)	override;

	UFUNCTION(BlueprintCallable, Category = "Miku")
		void ResetShotTimer();

	UFUNCTION(BlueprintCallable, Category = "Miku")
		void SetCooldown(const float& NewCooldown);

	virtual void ShootBullet() override;

	virtual int GetScoreAmount() override;
};
