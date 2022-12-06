// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LylatEnemy.h"
#include "LylatJeffEnemy.generated.h"

/**
 * 
 */
UCLASS()
class LYLATWARSRE_API ALylatJeffEnemy : public ALylatEnemy
{
	GENERATED_BODY()
	
public:
	ALylatJeffEnemy();

	virtual void BeginPlay() override;

	/**Cooldown between two shots (in seconds)*/
	UPROPERTY(Category = "Jeff", EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
		float JeffShotCooldown = 5;
	/**Random Cooldown added between two shots (in seconds)*/
	UPROPERTY(Category = "Jeff", EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
		float JeffRandomCooldown = 2;

	UPROPERTY(Category = "Jeff", VisibleInstanceOnly, BlueprintReadOnly)
		float JeffShotTimer = 5;

	/**Horizontal range of the enemy in degrees (a value of 0 will lock the enemy to the front, 180 allows him to rotate completly)*/
	UPROPERTY(Category = "Jeff", EditAnywhere, BlueprintReadOnly, meta = (ClampMax = "180", ClampMin = "0"))
		float JeffHorizontalRange = 90;

	/**Vertical lower range of the enemy in degrees*/
	UPROPERTY(Category = "Jeff", EditAnywhere, BlueprintReadOnly, meta = (ClampMax = "180", ClampMin = "0"))
		float JeffVerticalMinRange = 10;

	/**Vertical upper range of the enemy in degrees*/
	UPROPERTY(Category = "Jeff", EditAnywhere, BlueprintReadOnly, meta = (ClampMax = "180", ClampMin = "0"))
		float JeffVerticalMaxRange = 50;

	/**Max detection range of the enemy, player farther away will be ignored*/
	UPROPERTY(Category = "Jeff", EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
		float JeffDetectionMaxRange = 5000;

	/**Should the enemy recalculate its position each frame (activate this if the enemy is on a rail)*/
	UPROPERTY(Category = "Jeff", EditAnywhere, BlueprintReadOnly)
		bool JeffShouldUpdateQuat = false;

	/**Mesh component for the turret*/
	UPROPERTY(Category = "Jeff", VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* TurretMesh;

	/**Mesh component for the cannon*/
	UPROPERTY(Category = "Jeff", VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* CannonMesh;

	void Behaviour_Implementation(float DeltaTime) override;

	void Animate_Implementation(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Jeff")
		void ResetShotTimer();

	UFUNCTION(BlueprintCallable, Category = "Jeff")
		void SetCooldown(const float& NewCooldown);

	/**Rotates the turret towards the player, will return false if the action fails (outside of rotation range, or too far away)*/
	UFUNCTION(BlueprintCallable, Category = "Jeff")
		bool FaceTowardsPlayer();

	virtual void ShootBullet() override;

	void UpdateQuat();
protected:
	FQuat invRotation;
	float defaultRot = 0.0f;
};
