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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic Rail|Parameters", meta = (ClampMin = "0"))
		float railSpeed = 1;

	/*"Scale" of the speed. To be multiplied with railSpeed.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic Rail|Parameters", meta = (ClampMin = "0"))
		float speedMultiplier = 100;

	/**If true, will spawn ActorToSpawn on startup*/
	UPROPERTY(EditAnywhere, Category = "Generic Rail|Parameters")
		bool SpawnActor = true;

	/**Delay between spawn of entities*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic Rail|Parameters")
		float SpawnDelay = 0;
	/**If true, will spawn infinite actors, looping trough the actor list*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic Rail|Parameters")
		bool InifiniteSpawn = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generic Rail|Parameters")
		bool IsActivated = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SpawnActorsOnRail();

	virtual void ComputeRailDistance(float DeltaTime, ALylatEntity* Entity);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**Attach the actors to this rail, keeping it's relative position*/
	UFUNCTION(BlueprintCallable)
		void JoinRail(TSubclassOf<ALylatEntity> Actor);
	/**Attach all actors from the array to this rail, keeping their relative position*/
	UFUNCTION(BlueprintCallable)
		void JoinRailArray(TArray<ALylatEntity*> Actors);
	/**Set rail speed*/
	UFUNCTION(BlueprintCallable)
		void SetRailSpeed(const float& NewSpeed);
	/**Return true if the rail is about to loop*/
	UFUNCTION(BlueprintCallable)
		bool RailShouldLoop(ALylatEntity* Entity);
	/**Destroy all actors referenced on the rail*/
	UFUNCTION(BlueprintCallable)
	void DestroyAllActors();
	/**Loop code*/
	UFUNCTION()
		void RailLoop(ALylatEntity* Entity);
	/**Spawn the next entity from the ActorsToSpawn list*/
	UFUNCTION(BlueprintCallable)
		void SpawnNextEntity();
	/**Spawn one entity on the rail*/
	UFUNCTION(BlueprintCallable)
		void SpawnEntity(ALylatEntity* Entity);

	UFUNCTION(BlueprintCallable)
		void Activate() { this->IsActivated = true; }
	UFUNCTION(BlueprintCallable)
		void Deactivate() { this->IsActivated = false; }

private :
	void InitRail();
	
	void ComputeEnityMeshTransform(ALylatEntity* Entity);

	void UpdateActorTransform(TSubclassOf<ALylatEntity> Entity, const float& DeltaTime);
	void UpdateActorTransform(ALylatEntity* Entity, const float& DeltaTime);
	
		void UpdateAllActorsTransform(const float& DeltaTime);

	void UpdateEntitySpawning(float DeltaTime);

	bool ShouldSpawn();

private :
	float SpawnTimer = 0;
	int NextEntityIndex = 0;
	bool ActorsAreSpawned = false;
};
