// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "LylatGenericRail.generated.h"

UCLASS()
class LYLATWARSRE_API ALylatGenericRail : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALylatGenericRail();
			
	/*Spline component defining the path of the rail*/
	UPROPERTY(EditAnywhere, Category = "Generic Rail")
	class USplineComponent* SplineComponent;

	/*Rail will spawn and act on this actor*/
	UPROPERTY(EditAnywhere, Category = "Generic Rail")
		TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(BlueprintReadOnly)
		AActor* spawnedActor; //TODO : Better typing ? AActor kinda suck

	UPROPERTY(BlueprintReadOnly)
		TArray<TSubclassOf<AActor>> ActorsOnRail;

	/*Rail will start to drag the actor after this delay*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic Rail|Parameters", meta = (ClampMin = "0"))
		float railStartDelay = 0;

	/*Mouvement speed on the rail*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic Rail|Parameters") //Can change speed on the fly
		float railSpeed = 1;

	/*"Scale" of the speed. To be multiplied with railSpeed.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic Rail|Parameters", meta = (ClampMin = "0")) //Can change speed on the fly
		int speedMultiplier = 100;

	/**If true, will spawn ActorToSpawn on startup*/
	UPROPERTY(EditAnywhere, Category = "Generic Rail|Parameters")
		bool SpawnActor = true;

protected :
	/*Time ealapsed*/
	UPROPERTY(BlueprintReadOnly, Category = "Generic Rail")
		float railTime = 0; //Bad idea to put this as UPROPERTY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpawnActorOnRail();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void JoinRail(TSubclassOf<AActor> Actor);

private :
	void InitRail();
	
	void UpdateActorTransform(TSubclassOf<AActor> Actor, const float& Time);
	void UpdateActorTransform(AActor *Actor, const float& Time);
	void UpdateAllActorsTransform(const float& Time);
};
