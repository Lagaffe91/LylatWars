#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

#include "LylatNormalBullet.generated.h"

UCLASS()
class LYLATWARSRE_API ALylatNormalBullet : public AActor
{
	GENERATED_BODY()

public:
	UProjectileMovementComponent *BulletMovement;
	UPROPERTY(Category = "Lylat Bullet", VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent         *SphereMesh;
	UPROPERTY(Category = "Lylat Bullet", VisibleAnywhere, BlueprintReadOnly)
	USphereComponent             *CollisionComponent;

	UPROPERTY(Category = "Lylat Bullet", EditAnywhere, BlueprintReadOnly)
		float BulletSpeed = 3000.0f;

	UPROPERTY(Category = "Lylat Bullet", EditAnywhere, BlueprintReadOnly)
		float BulletLifeTime = 3.0f;
	AActor* owner = nullptr;
	bool isPlayerSpawned = false;
public:	
	// Sets default values for this actor's properties
	ALylatNormalBullet(const FObjectInitializer& ObjectInitializer);

	// Sets the bullet of the mesh
	void SetBulletMesh(UStaticMesh *mesh);

	void SetInitialSpeed(float InitialSpeed);

	void FireInDirection(const FVector& ShootDirection, AActor* ownerIn, bool playerSpawned = false);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void HitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
