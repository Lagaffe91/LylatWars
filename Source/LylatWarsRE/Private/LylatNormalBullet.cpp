#include "LylatNormalBullet.h"
#include "LylatEntity.h"
#include "DebugString.h"
#include "LylatPlayerPawn.h"

// Sets default values
ALylatNormalBullet::ALylatNormalBullet(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if(!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));
	}

	BulletMovement     = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	SphereMesh         = CreateDefaultSubobject<UStaticMeshComponent>        (TEXT("SphereMesh"));
	CollisionComponent = CreateDefaultSubobject<USphereComponent>            (TEXT("CollisionComponent"));

	//TODO: change this value to be reasonable
	CollisionComponent->InitSphereRadius(15.0f);

	BulletMovement->SetUpdatedComponent(CollisionComponent);
	BulletMovement->InitialSpeed = 3000.0f;
	BulletMovement->MaxSpeed = 3000.0f;
	BulletMovement->bRotationFollowsVelocity = true;
	BulletMovement->bShouldBounce = true;
	BulletMovement->Bounciness = 0.3f;
	BulletMovement->ProjectileGravityScale = 0.0f;
	RootComponent = CollisionComponent;
	InitialLifeSpan = 3.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
	SphereMesh->SetupAttachment(RootComponent);
	SetActorScale3D(FVector(0.2f, 0.2f, 0.2f));
}

void ALylatNormalBullet::FireInDirection(const FVector& ShootDirection, AActor* ownerIn, bool playerSpawned)
{
	BulletMovement->Velocity = ShootDirection * BulletMovement->InitialSpeed;
	owner = ownerIn;
	isPlayerSpawned = playerSpawned;
}
// Called when the game starts or when spawned
void ALylatNormalBullet::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // We want overlaps.
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	CollisionComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALylatNormalBullet::HitboxBeginOverlap);

	SphereMesh->SetGenerateOverlapEvents(true);
	SphereMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // We want overlaps.
	SphereMesh->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereMesh->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALylatNormalBullet::HitboxBeginOverlap);
}

void ALylatNormalBullet::SetBulletMesh(UStaticMesh *mesh)
{
	if (mesh)
		SphereMesh->SetStaticMesh(mesh);
}
// Called every frame
void ALylatNormalBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALylatNormalBullet::HitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == owner) return;
	ALylatNormalBullet* bullet = Cast<ALylatNormalBullet>(OtherActor);
	if (bullet)
	{
		if (!bullet->owner || isPlayerSpawned == bullet->isPlayerSpawned) return;
		//Debug("Touched bullet",0);
		Destroy();
	}
	else
	{
		ALylatEntity* entity = Cast<ALylatEntity>(OtherActor);
		if (entity)
		{
			if (entity->EntityLife <= 0) return;
			ALylatPlayerPawn* player = Cast<ALylatPlayerPawn>(OtherActor);
			if ((bool)player != isPlayerSpawned)
			{
				//Debug("Touched %s, %d", *entity->GetName(), entity->EntityLife);
				entity->TakeBulletDamage(this);
				Destroy();
			}
		}
		else
		{
			Destroy();
			//Debug("Touched anything", 0);
		}
	}
}