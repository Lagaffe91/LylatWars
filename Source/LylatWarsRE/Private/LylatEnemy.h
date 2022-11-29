// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LylatEntity.h"
#include "LylatEnemy.generated.h"

UCLASS()
class ALylatEnemy : public ALylatEntity
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALylatEnemy();

public :
	/**If false, will be completely harmless*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lylat Enemy|Parameters")
		bool IsActivated = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Lylat Enemy|Events")
		void Activate();

	/**Called once per tick if enemy is activated*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Lylat Enemy|Mouvement")
		void Behaviour(float DeltaTime);
	virtual void Behaviour_Implementation(float DeltaTime) {};

	/**Shoot a bullet following it's implementation*/
	UFUNCTION(BlueprintCallable, Category = "Lylat Enemy|Events")
		virtual void ShootBullet() {};
};
