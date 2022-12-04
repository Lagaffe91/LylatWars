// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LylatEnemy.h"
#include "LylatFalconEnemy.generated.h"

/**
 * 
 */
UCLASS()
class LYLATWARSRE_API ALylatFalconEnemy : public ALylatEnemy
{
	GENERATED_BODY()
public :
	/**Cooldown between two shots (in seconds)*/
	UPROPERTY(Category = "Falcon", EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
		float FalconRollCooldown = 5;
	/**Random number between 0 and FalcomRandomCooldown to be added to the original cooldown for more variations*/
	UPROPERTY(Category = "Falcon", EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
		int FalcomRandomCooldown = 5;
	/**Animation duration (in seconds)*/
	UPROPERTY(Category = "Falcon", EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
		float AnimationDuration = 0.5;

	/**Represent the state of the roll cooldown (in seconds)*/
	UPROPERTY(Category = "Falcon", VisibleInstanceOnly, BlueprintReadOnly)
		float FalconRollTimer = 0;
	/**Represent the state of the animation (in seconds)*/
	UPROPERTY(Category = "Falcon", VisibleInstanceOnly, BlueprintReadOnly)
		float AnimationTimer = 0;
	

public : 
	void Behaviour_Implementation(float DeltaTime);

	void Animate_Implementation(float DeltaTime);

	virtual int GetScoreAmount() override;

private :
	void DoBarrelRoll(float DeltaTime);
	void ResetRollCooldown();

private :
	bool isRolling = false; 
};
