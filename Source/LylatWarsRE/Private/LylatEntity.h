// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/ArrowComponent.h"
#include "LylatGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
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
	TArray<UStaticMeshComponent*> meshes;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**Mesh component for the look of the entity*/
	UPROPERTY(Category = "Lylat Entity", VisibleAnywhere, BlueprintReadOnly)
		class UStaticMeshComponent* EntityMesh;

	/**Material used for the damage animation*/
	UPROPERTY(Category = "Lylat Entity", EditAnywhere, BlueprintReadOnly)
		class UMaterialInterface* DamageMaterial;

	/**UBoxComponent representing the hitbox of the entity**/
	UPROPERTY(Category = "Lylat Entity", VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* EntityHitbox;
	/**Location of spawning bullets **/
	UPROPERTY(Category = "Lylat Entity", VisibleAnywhere, BlueprintReadOnly)
		class UArrowComponent* BulletSpawnPosition;

	/**Amount of points dropped by the entity*/
	UPROPERTY(Category = "Lylat Entity", EditAnywhere, BlueprintReadOnly)
		int EntityScoreValue = 0;

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

	/**Blueprint of the explosion effect on death*/
	UPROPERTY(Category = "Lylat Entity", EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AActor> Explosion_BP;

	/**Should the entity plas sounds ?*/
	UPROPERTY(Category = "Lylat Entity", EditAnywhere, BlueprintReadOnly)
		bool ShouldPlaySound = false;

	/**Sound of the engine, will play at initialisation*/
	UPROPERTY(Category = "Lylat Entity", EditAnywhere, BlueprintReadOnly)
		UAudioComponent* EngineSound = nullptr;

	/**Shooting sound*/
	UPROPERTY(Category = "Lylat Entity", EditAnywhere, BlueprintReadOnly)
		UAudioComponent* ShootSound = nullptr;

public:

	UFUNCTION()
	virtual void HitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void TakeBulletDamage(ALylatNormalBullet* bullet, int amount = 1);

	UFUNCTION(BlueprintCallable)
	virtual void TakeEntityDamage(AActor* entity);

	UFUNCTION(BlueprintCallable)
	virtual void DestroyEntity(bool addScore = true);

	UFUNCTION(BlueprintCallable)
	virtual void PlayLaserSound();

	/**if the entity is on a rail, Will be called when entity is at the end of the rail*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Lylat Entity|Events")
		void RailEnded();
	void RailEnded_Implementation();

	/**Will be called when the entity takes a hit*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Lylat Entity|Events")
		void TakeDamageEvent();
	void TakeDamageEvent_Implementation();

	/**Will be called at the end of the invulnerability timer*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Lylat Entity|Events")
		void EndDamageEvent();
	void EndDamageEvent_Implementation();

	/**Will be called when entity is destoryed*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Lylat Entity|Events")
		void OnDestroy();
	void OnDestroy_Implementation() {};
};
