// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LylatEntity.h"
#include "DebugString.h"
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
	/**Will activate after a delay (if not already activated)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lylat Enemy|Parameters", meta = (ClampMin = "0"))
		float ActivtionDelay = 0;
	/**Reference to the player*/
	UPROPERTY(BlueprintReadWrite, Category = "Lylat Enemy|References")
		class ALylatPlayerPawn* PlayerReference;
	UPROPERTY(Category = "Lylat Enemy|Parameters", EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0"))
		float AnimationSpeed = 1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/**Will activate the enemy (start the core behaviour)*/
	UFUNCTION(BlueprintCallable, Category = "Lylat Enemy|Events")
		void Activate();
	/**Will desactivate the enemy (stop the core behaviour)*/
	UFUNCTION(BlueprintCallable, Category = "Lylat Enemy|Events")
		void Desactivate();
	/**Called once per tick if enemy is activated*/
	UFUNCTION(BlueprintNativeEvent, Category = "Lylat Enemy|Mouvement")
		void Behaviour(float DeltaTime);
	virtual void Behaviour_Implementation(float DeltaTime) {};
	/**This function will be called every tick, used "animation"*/
	UFUNCTION(BlueprintNativeEvent, Category = "Lylat Enemy|Animation")
		void Animate(float DeltaTime);
	virtual void Animate_Implementation(float DeltaTime) {};
	/**Shoot a bullet following it's implementation*/
	UFUNCTION(BlueprintCallable, Category = "Lylat Enemy|Events")
		virtual void ShootBullet() { Debug("This enemy cant shoot !",0); };

	virtual void TakeEntityDamage(AActor* entity) override;


private : 
	bool shouldUpdateDelay = false;
};
