// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/ArrowComponent.h"
#include "LylatGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "LylatEntity.generated.h"

class ALylatNormalBullet;

UCLASS()
class ALylatEntity : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALylatEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**Mesh component for the look of the entity*/
	UPROPERTY(Category = "Lylat Entity", VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* EntityMesh;

	/**UBoxComponent representing the hitbox of the entity**/
	UPROPERTY(Category = "Lylat Entity", VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* EntityHitbox;
	/**Location of spawning bullets **/
	UPROPERTY(Category = "Lylat Entity", VisibleAnywhere, BlueprintReadOnly)
		class UArrowComponent* BulletSpawnPosition;

	/**Max life of the entity*/
	UPROPERTY(Category = "Lylat Entity", EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1"))
		int EntityMaxLife = 1;
	/**Current life of the entity*/
	UPROPERTY(Category = "Lylat Entity", VisibleAnywhere, BlueprintReadOnly)
		int EntityLife = 0;
	/**Invulnerability timer*/
	UPROPERTY(Category = "Lylat Entity", EditAnywhere, BlueprintReadOnly)
		float EntityInvulneability = 1.5;
	/**Invulnerability current timer*/
	UPROPERTY(Category = "Lylat Entity", VisibleAnywhere, BlueprintReadOnly)
		float EntityCurrentInvulneability = 0.0f;

	/**Distance on the rail*/
	UPROPERTY(Category = "Lylat Entity", EditAnywhere, BlueprintReadOnly)
		float EntityRailDistance = 0;
	/**True if entity is on a rail*/
	UPROPERTY(Category = "Lylat Entity", VisibleAnywhere, BlueprintReadOnly)
		bool EntityIsOnARail = false;

	/**Type of bullets shot by the entity*/
	UPROPERTY(Category = "Lylat Entity", EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ALylatNormalBullet> BulletType;

public:

	UFUNCTION()
	virtual void HitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void TakeBulletDamage(ALylatNormalBullet* bullet);

	UFUNCTION(BlueprintCallable)
	virtual void TakeEntityDamage(AActor* entity);

	UFUNCTION(BlueprintCallable)
	virtual void DestroyEntity(bool addScore = true);

	/**if the entity is on a rail, Will be called when entity is at the end of the rail*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Lylat Entity|Events")
		void RailEnded();
	void RailEnded_Implementation();

	/**Will be called when entity is destoryed*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Lylat Entity|Events")
		void OnDestroy();
	void OnDestroy_Implementation() {};
};
