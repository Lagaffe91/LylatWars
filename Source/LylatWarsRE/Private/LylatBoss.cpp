// Fill out your copyright notice in the Description page of Project Settings.


#include "LylatBoss.h"
#include "LylatWeakPoint.h"
#include "Kismet/GameplayStatics.h"	
#include "LylatWarsRE/Public/LylatHomingBullet.h"


// Sets default values
ALylatBoss::ALylatBoss()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Lives = 5.0f;
	IsDead = false;
	CanFire = false;
	IsAttacking = false;
	BulletCooldown = 0.0f;



	USceneComponent* Boss = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));


	BossMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BossMesh"));
	BossMesh->SetRelativeLocationAndRotation(BossPosition, FQuat::MakeFromEuler(BossRotation));
	BossMesh->SetupAttachment(Boss);

#if 1
	BossLefGun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftGun"));
	BossLefGun->SetRelativeLocationAndRotation(LeftGunPosition, FQuat::MakeFromEuler(BossRotation));
	BossLefGun->SetupAttachment(Boss);

	BossRightGun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightGun"));
	BossRightGun->SetRelativeLocationAndRotation(RightGunPosition, FQuat::MakeFromEuler(BossRotation));
	BossRightGun->SetupAttachment(Boss);
#endif


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

#if 1
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			FVector Location1 = BossLefGun->GetComponentLocation();
			FRotator Rotation1 = BossRotation.Rotation();
			ALylatNormalBullet* Projectile1 = GetWorld()->SpawnActor<ALylatNormalBullet>(ALylatNormalBullet::StaticClass(), Location1, Rotation1, SpawnParams);
			if (Projectile1)
			{
				FVector LaunchDirection1 = BossLefGun->GetForwardVector();
				Projectile1->FireInDirection(LaunchDirection1, this);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FIRE 1!!")));

			}

			FVector Location2 = BossRightGun->GetComponentLocation();
			FRotator Rotation2 = BossRotation.Rotation();
			ALylatNormalBullet* Projectile2 = GetWorld()->SpawnActor<ALylatNormalBullet>(ALylatNormalBullet::StaticClass(), Location2, Rotation2, SpawnParams);
			if (Projectile2)
			{
				FVector LaunchDirection2 = BossRightGun->GetForwardVector();
				Projectile2->FireInDirection(LaunchDirection2, this);

				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FIRE 2!!")));


			}
#endif
			BulletCooldown = 0.5f;

		}


#if 0
		ALylatHomingBullet
		if (CanFire)
			Fire();

		if (IsAttacking)
			Attack();

#endif

		

	}
}

// Called to bind functionality to input
void ALylatBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ALylatBoss::BasicMovement(float deltaTime)
{

#if 0
	BossRotation.Z += FMath::Cos(deltaTime) / 2;
	BossRotation.X -= FMath::Sin(deltaTime) / 4;
#endif


	BossMesh->SetRelativeLocationAndRotation(BossPosition, FQuat::MakeFromEuler(BossRotation));

	BossLefGun->SetRelativeLocationAndRotation(LeftGunPosition, FQuat::MakeFromEuler(BossRotation));
	BossRightGun->SetRelativeLocationAndRotation(RightGunPosition, FQuat::MakeFromEuler(BossRotation));



}

void ALylatBoss::Fire()
{

#if 0
	
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FireParticle, BossMesh->GetForwardVector(), FRotator::ZeroRotator, true);
#endif

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("FIREEEEEEE !!")));
}



void ALylatBoss::Attack()
{
	//TODO(o.luanda): Do attack 
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("ATTAAAAACK")));
}
