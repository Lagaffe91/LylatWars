#include "LylatJeffEnemy.h"

#include "LylatPlayerPawn.h"

#include "DebugString.h"

ALylatJeffEnemy::ALylatJeffEnemy()
{
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(EntityMesh);
	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(TurretMesh);
	ResetShotTimer();
}

void ALylatJeffEnemy::BeginPlay()
{
	Super::BeginPlay();
	defaultRot = TurretMesh->GetRelativeRotation().Euler().Z;
	UpdateQuat();
}

void ALylatJeffEnemy::Behaviour_Implementation(float DeltaTime)
{
	if (!PlayerReference)
	{
		DebugError("NO PLAYER REFERENCE      AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",0);
		return;
	}
	if (JeffShouldUpdateQuat)
	{
		UpdateQuat();
	}
	bool facing = FaceTowardsPlayer();
	if (JeffShotTimer > 0)
	{
		JeffShotTimer -= DeltaTime;
	}
	else if (facing)
	{
		ResetShotTimer();
		ShootBullet();
	}
}

void ALylatJeffEnemy::Animate_Implementation(float DeltaTime)
{
}

void ALylatJeffEnemy::ResetShotTimer()
{
	JeffShotTimer = JeffShotCooldown + FMath::RandRange(0.f, JeffRandomCooldown);
}

void ALylatJeffEnemy::SetCooldown(const float& NewCooldown)
{
	if (NewCooldown > 0)
	{
		JeffShotCooldown = NewCooldown;
	}
}

bool ALylatJeffEnemy::FaceTowardsPlayer()
{
	FVector dir = PlayerReference->EntityMesh->GetComponentLocation() - CannonMesh->GetComponentLocation();
	if (dir.Size() > JeffDetectionMaxRange) return false;
	dir.Normalize();
	dir = invRotation * dir;
	FVector targetRotation = dir.ToOrientationQuat().Euler();
	targetRotation.Z -= defaultRot;
	if (targetRotation.Z < -JeffHorizontalRange || targetRotation.Z > JeffHorizontalRange ||
		targetRotation.Y < -JeffVerticalMinRange || targetRotation.Y > JeffVerticalMaxRange) return false;
	targetRotation.Z += defaultRot;
	TurretMesh->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0, 0, targetRotation.Z)));
	CannonMesh->SetRelativeRotation(FQuat::MakeFromEuler(FVector(0,targetRotation.Y,0)));
	return true;
}

void ALylatJeffEnemy::ShootBullet()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector Location = CannonMesh->GetComponentLocation();
	FRotator Rotation = CannonMesh->GetComponentRotation();
	ALylatNormalBullet* Projectile = GetWorld()->SpawnActor<ALylatNormalBullet>(BulletType, Location, Rotation, SpawnParams);

	if (Projectile)
	{
		//Set the projectile's initial trajectory.
		FVector LaunchDirection = CannonMesh->GetComponentQuat().GetForwardVector();
		Projectile->FireInDirection(LaunchDirection, this);
	}
}

void ALylatJeffEnemy::UpdateQuat()
{
	invRotation = RootComponent->GetComponentQuat().Inverse();
}
