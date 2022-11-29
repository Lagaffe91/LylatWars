// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatBoss.h"
#include "LylatWeakPoint.h"
#include "Kismet/GameplayStatics.h"	


// Sets default values
ALylatBoss::ALylatBoss()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Lives = 5.0f;
	IsDead = false;
	BulletCooldown = 0.0f;



	USceneComponent* Boss = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));


	BossMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BossMesh"));
	BossMesh->SetRelativeLocationAndRotation(BossPosition, FQuat::MakeFromEuler(BossRotation));
	BossMesh->SetupAttachment(Boss);

}

// Called when the game starts or when spawned
void ALylatBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALylatBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BulletCooldown -= DeltaTime;

	if (!IsDead)
	{
		BasicMovement(DeltaTime);

		if (BulletCooldown <= 0.0f)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			FVector Location = BossMesh->GetRelativeLocation() + GetRootComponent()->GetRelativeLocation();
			FRotator Rotation = BossRotation.Rotation();
			ALylatNormalBullet* Projectile = GetWorld()->SpawnActor<ALylatNormalBullet>(ALylatNormalBullet::StaticClass(), Location, Rotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = BossMesh->GetForwardVector();
				Projectile->FireInDirection(LaunchDirection);
			}

			BulletCooldown = 0.5f;

		}



	}
}

// Called to bind functionality to input
void ALylatBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALylatBoss::BasicMovement(float deltaTime)
{

	BossRotation.Z += FMath::Cos(deltaTime) / 2;
	BossRotation.X -= FMath::Sin(deltaTime) / 4;


	BossMesh->SetRelativeLocationAndRotation(BossPosition, FQuat::MakeFromEuler(BossRotation));

}



