#include "LylatBombBullet.h"
#include <LylatEntity.h>
#include <LylatEnemy.h>
#include <LylatPlayerPawn.h>

ALylatBombBullet::ALylatBombBullet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BombCurrentTimer = 0.0f;
	defaultMeshSize = SphereMesh->GetComponentScale();
}

void ALylatBombBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BombCurrentTimer += DeltaTime;
	float decayLimit = BombTimer + BombExplosionTimer;
	bool exploding = BombCurrentTimer > BombTimer;
	bool decaying = BombCurrentTimer > decayLimit;
	bool finished = BombCurrentTimer > decayLimit + BombDecayTimer;
	if (exploding && !decaying)
	{
		float factor = (BombCurrentTimer - BombTimer) / BombExplosionTimer;
		SphereMesh->SetRelativeScale3D(defaultMeshSize * FMath::Lerp(1.0f, BombRadius, FMath::Pow(factor, 0.5f)));
	}
	else if (decaying && !finished)
	{
		if (!IsBloated)
		{
			IsBloated = true;
			if (BombTouchAllBullets)
			{
				TArray<AActor*> FoundActors;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALylatNormalBullet::StaticClass(), FoundActors);
				for (AActor* bullet : FoundActors)
				{
					ALylatNormalBullet* b = Cast<ALylatNormalBullet>(bullet);
					if (!b->isPlayerSpawned) b->Destroy();
				}
			}
			if (BombTouchAllEnemies)
			{
				TArray<AActor*> FoundActors;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALylatEnemy::StaticClass(), FoundActors);
				for (AActor* enemy : FoundActors)
				{
					ALylatEnemy* e = Cast<ALylatEnemy>(enemy);
					if (e != owner) e->TakeBulletDamage(this);
				}
			}
		}
		float factor = 1.0f - (BombCurrentTimer - decayLimit) / BombDecayTimer;
		SphereMesh->SetRelativeScale3D(defaultMeshSize * FMath::Lerp(1.0f, BombRadius, FMath::Pow(factor, 0.5f)));
	}
	else if (finished)
	{
		Destroy();
	}
}

void ALylatBombBullet::HitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == owner || BombCurrentTimer <= BombTimer) return;
	ALylatEntity* entity = Cast<ALylatEntity>(OtherActor);
	if (entity)
	{
		if (entity->EntityLife <= 0 || entity->EntityCurrentInvulneability > 0.0f) return;
		ALylatPlayerPawn* player = Cast<ALylatPlayerPawn>(OtherActor);
		if ((bool)player != isPlayerSpawned)
		{
			//Debug("Touched %s, %d", *entity->GetName(), entity->EntityLife);
			entity->TakeBulletDamage(this);
			entity->EntityCurrentInvulneability = entity->EntityInvulneability;
		}
	}
}

void ALylatBombBullet::BeginPlay()
{
	Super::BeginPlay();
	BombCurrentTimer = 0.0f;
	defaultMeshSize = SphereMesh->GetRelativeScale3D();
}
