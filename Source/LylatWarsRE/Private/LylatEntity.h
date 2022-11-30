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

public:

	UFUNCTION()
	virtual void HitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void TakeBulletDamage(ALylatNormalBullet* bullet);

	UFUNCTION()
	virtual void TakeEntityDamage(AActor* entity);

	UFUNCTION()
	virtual void DestroyEntity();
};
