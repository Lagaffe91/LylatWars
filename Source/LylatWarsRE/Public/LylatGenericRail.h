// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LylatEntity.h"

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
		TArray<TSubclassOf<ALylatEntity>> ActorsToSpawn;

	UPROPERTY(BlueprintReadOnly)
		TArray<ALylatEntity*> ActorsOnRail;

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
	/**True if the rail is not active*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Generic Rail|Parameters")
		bool RailIsOver = false;
protected :
	/*Time ealapsed*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Generic Rail")
		float railTime = 0; //Bad idea to put this as UPROPERTY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpawnActorsOnRail();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void JoinRail(TSubclassOf<ALylatEntity> Actor);
	UFUNCTION(BlueprintCallable)
		void JoinRailArray(TArray<ALylatEntity*> Actors);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Generic Rail|Events")
		void RailEnded();
	void RailEnded_Implementation();

	UFUNCTION(BlueprintCallable)
		bool RailShouldLoop();

	UFUNCTION(BlueprintCallable)
		void RailLoop();

private :
	void InitRail();
	
	void ComputeEnityMeshTransform(ALylatEntity* Entity);

	void UpdateActorTransform(TSubclassOf<ALylatEntity> Actor, const float& Time);
	void UpdateActorTransform(ALylatEntity*Actor, const float& Time);
	void UpdateAllActorsTransform(const float& Time);
};
