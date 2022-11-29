// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatNormalBullet.h"

// Sets default values
ALylatNormalBullet::ALylatNormalBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if(!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	BulletMovement     = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	SphereMesh         = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));

	CollisionComponent->InitSphereRadius(15.0f);

	BulletMovement->SetUpdatedComponent(CollisionComponent);
	BulletMovement->InitialSpeed = 3000.0f;
	BulletMovement->MaxSpeed = 3000.0f;
	BulletMovement->bRotationFollowsVelocity = true;
	BulletMovement->bShouldBounce = true;
	BulletMovement->Bounciness = 0.3f;
	BulletMovement->ProjectileGravityScale = 0.0f;
	RootComponent = CollisionComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	SphereMesh->SetupAttachment(RootComponent);
	SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));
}

void ALylatNormalBullet::FireInDirection(const FVector& ShootDirection)
{
	BulletMovement->Velocity = ShootDirection * BulletMovement->InitialSpeed;
}
// Called when the game starts or when spawned
void ALylatNormalBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALylatNormalBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

