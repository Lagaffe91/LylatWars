#include "LylatPlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "LylatPlayerRail.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

#include "DebugString.h"

// Sets default values
ALylatPlayerPawn::ALylatPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	PlayerTrailMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerShipTrailMesh"));
	PlayerTrailMesh->SetupAttachment(EntityMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraPosition.X = CameraDistance;
	Camera->SetRelativeLocationAndRotation(CameraPosition, FQuat::MakeFromEuler(CameraRotation));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = false;
	isShooting = false;
}

// Called when the game starts or when spawned
void ALylatPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	DefaultTrailSize = PlayerTrailMesh->GetRelativeScale3D();
	LastPosition = GetActorLocation();
	resetGyro = true;
	defaultPlayerPos = EntityMesh->GetRelativeLocation();
	defaultPlayerRot = EntityMesh->GetRelativeRotation().Euler();
	gyroInput = FVector2D::ZeroVector;

	ALylatPlayerRail* playerRail = (ALylatPlayerRail*)UGameplayStatics::GetActorOfClass(this->GetWorld(), ALylatPlayerRail::StaticClass());
	if (playerRail)
	{
		this->PlayerRail = playerRail;
	}
	else
	{
		DebugError("failed to grab rail reference", 0);
	}
}

void ALylatPlayerPawn::MoveUpInput(float input)
{
	Velocity.Z += input * PlayerMaxSpeed;
}

void ALylatPlayerPawn::MoveRightInput(float input)
{
	Velocity.Y += input * PlayerMaxSpeed;
}

void ALylatPlayerPawn::MovementGyroInput(FVector value)
{
	Debug("Gyro: %.2f %.2f %.2f", value.X, value.Y, value.Z);
	if (resetGyro)
	{
		defaultRotation = FQuat::MakeFromEuler(value).Inverse();
		gyroInput = FVector2D::ZeroVector;
		resetGyro = false;
	}
	else
	{
		FQuat deltaRotation = FQuat::MakeFromEuler(value) * defaultRotation;
		float angle = FMath::RadiansToDegrees(deltaRotation.GetAngle());
		float tmp = FMath::Abs(angle);
		if (tmp > 0.1f && tmp < 3.0f)
		{
			FVector axis = deltaRotation.GetForwardVector();
			gyroInput.Y = axis.Y * PlayerMaxSpeed * 70.0f;
			gyroInput.X = axis.Z * PlayerMaxSpeed * -70.0f;
		}
		else
		{
			gyroInput = FVector2D::ZeroVector;
		}
	}
}

void ALylatPlayerPawn::TouchDown(ETouchIndex::Type FingerIndex, FVector Location)
{
	isTouched = true;
	touchStart = FVector2D(Location.X, Location.Y);
	touchLast = touchStart;
	touchCurrent = touchStart;
}

void ALylatPlayerPawn::TouchDrag(ETouchIndex::Type FingerIndex, FVector Location)
{
	touchCurrent = FVector2D(Location.X, Location.Y);
}

void ALylatPlayerPawn::TouchUp(ETouchIndex::Type FingerIndex, FVector Location)
{
	isTouched = false;
	touchVel = FVector2D::ZeroVector;
}

void ALylatPlayerPawn::ActionStopShoot()
{
	isShooting = false;
}

void ALylatPlayerPawn::ActionShoot()
{
	isShooting = true;
}
void ALylatPlayerPawn::UpdateDash(float DeltaTime)
{
	if(IsDashing)
	{
		if (this->DashGauge > 0)
		{
			this->DashTimer += DeltaTime;
			
			//Acceleration
			if (this->PlayerRail)
			{
				this->PlayerRail->PlayerDashSpeed = FMath::Lerp(0.0f, DashMaxSpeed, this->DashTimer * this->DashAcceleration);
			}
			else
			{
				DebugError("Dash : Mising player rail reference !", 0);
			}

			this->DashGauge -= DeltaTime * DashDrain;
		}
		else //No more stamina
		{
			this->IsDashing = false;
			DashDecelerationTimer = 0;
			DashMaxSpeedAtteigned = this->PlayerRail->PlayerDashSpeed;
			DashShouldDecelerate = true;
		}
	}
	else
	{
		if (DashShouldDecelerate)
		{
			if (DashDecelerationTimer < 1)
			{
				DashDecelerationTimer += DeltaTime;
			}

			//Deceleration
			if (this->PlayerRail)
			{
				this->PlayerRail->PlayerDashSpeed = FMath::Lerp(DashMaxSpeedAtteigned, 0.f, DashDecelerationTimer);
			}
			else
			{
				DebugError("Dash : Mising player rail reference !", 0);
			}

			if (this->PlayerRail->PlayerDashSpeed <= 0)
			{
				DashShouldDecelerate = false;
			}
		}
		//Reset Dash
		this->DashTimer = 0;

		//Gauge regeneration
		this->DashGauge = FMath::Clamp(this->DashGauge+(DeltaTime*DashRegeneration),0.f,1.f);
	}
}
void ALylatPlayerPawn::UpdateShooting(float DeltaTime)
{
	if (ShootCD > 0.0f || (!isShooting && !isTouched)) return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	FVector Location = BulletSpawnPosition->GetComponentLocation();
	FRotator Rotation = PlayerRotation.Rotation();
	ALylatNormalBullet* Projectile = GetWorld()->SpawnActor<ALylatNormalBullet>(BulletType, Location, Rotation, SpawnParams);
	if (Projectile)
	{
		// Set the projectile's initial trajectory.
		FVector LaunchDirection = EntityMesh->GetForwardVector();
		Projectile->FireInDirection(LaunchDirection, this, true);
		if (PlayerBulletMesh)
		{
			Projectile->SetBulletMesh(PlayerBulletMesh);
		}
	}
	ShootCD = ShootCooldown;
}
void ALylatPlayerPawn::ActionBarrelRoll(bool reversed)
{
	if (BarrelRollCD > 0.0f || BarrelRollAnim > 0.0f) return;
	barrelReversed = reversed;
	BarrelRollAnim = BarrelRollSpeed;
	BarrelRollCD = BarrelRollCooldown;
}

void ALylatPlayerPawn::ActionDash()
{
	if (this->DashGauge > this->DashInitialCost)
	{
		this->IsDashing = true;
		Debug("Dash", 0);
	}
	else
	{
		Debug("Not enough power to dash !", 0);
	}
}

void ALylatPlayerPawn::ActionStopDash()
{
	this->IsDashing = false;
}

void ALylatPlayerPawn::ActionResetGyro()
{
	resetGyro = true;
}

void ALylatPlayerPawn::UpdatePlayer(float DeltaTime)
{
	

	SetupBarrelRollAnim(DeltaTime);
	Velocity = FVector::ZeroVector;
	PlayerPosition.Y = FMath::Clamp(PlayerPosition.Y, -PlayerPlaneSize.X / 2, PlayerPlaneSize.X / 2);
	PlayerPosition.Z = FMath::Clamp(PlayerPosition.Z, -PlayerPlaneSize.Y / 2, PlayerPlaneSize.Y / 2);
	float rotationX = PlayerRotation.X;
	PlayerRotation = PlayerRotation * (1 - PlayerUnturnSpeed * DeltaTime);
	PlayerRotation.X = rotationX;
	EntityMesh->SetRelativeLocationAndRotation(PlayerPosition + defaultPlayerPos, FQuat::MakeFromEuler(PlayerRotation + defaultPlayerRot + FVector(PlayerRotation.Z * 0.5f, PlayerPosition.Z / PlayerPlaneSize.Y * 40, PlayerPosition.Y / PlayerPlaneSize.X * 80)));
}

void ALylatPlayerPawn::UpdateCamera(float DeltaTime)
{
	CameraPosition.X = CameraDistance;
	CameraPosition.Z = PlayerPosition.Z * CameraFollowRatio + (1 - CameraFollowRatio) * (PlayerPosition.Z / PlayerPlaneSize.Y * 2.0f) * (CameraDistance * (ViewportSize.Y / ViewportSize.X) + PlayerPlaneSize.Y * 0.5f);
	CameraPosition.Y = PlayerPosition.Y * CameraFollowRatio + (1 - CameraFollowRatio) * (PlayerPosition.Y / PlayerPlaneSize.X * 2.0f) * (CameraDistance + PlayerPlaneSize.X * 0.5f);
	Camera->SetRelativeLocation(CameraPosition);
	FVector Position = GetActorLocation();
	float length = PlayerTrailLength * (Position - LastPosition).Size() / DeltaTime;
	length = FMath::Clamp(length, 0.5f, 5.0f);
	PlayerTrailMesh->SetRelativeScale3D(FVector(length, 1, 1) * DefaultTrailSize);
	LastPosition = Position;
}

void ALylatPlayerPawn::SetupBarrelRollAnim(float DeltaTime)
{
	if (isTouched)
	{
		touchVel = (touchCurrent - touchLast) / DeltaTime;
		touchLast = touchCurrent;
		if (touchVel.X > 2000.0f) ActionBarrelRoll(false);
		else if (touchVel.X < -2000.0f) ActionBarrelRoll(true);
	}
	Velocity = (FVector(0, gyroInput.Y, gyroInput.X) + Velocity).GetClampedToMaxSize(PlayerMaxSpeed);
	BarrelRollCD -= DeltaTime;
	ShootCD -= DeltaTime;
	PlayerPosition += Velocity * DeltaTime;
	PlayerRotation.Y += Velocity.Z * DeltaTime * PlayerTurnSpeed;
	PlayerRotation.Z += Velocity.Y * DeltaTime * PlayerTurnSpeed;
	if (BarrelRollAnim <= 0.0f)
	{
		PlayerRotation.X = 0;
		EntityHitbox->SetActive(true);
	}
	else
	{
		PlayerRotation.X = FMath::Lerp(0.0f, barrelReversed ? 360.0f : -360.0f, BarrelRollAnim / BarrelRollSpeed);
		PlayerRotation.X = FMath::Fmod(PlayerRotation.X, 360.0f);
		if (PlayerRotation.X < -180.0f) PlayerRotation.X += 360.0f;
		if (PlayerRotation.X > 180.0f) PlayerRotation.X -= 360.0f;
		BarrelRollAnim -= DeltaTime;
		EntityHitbox->SetActive(false);
	}
}

// Called every frame
void ALylatPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ViewportSize.X <= 0.0f || ViewportSize.Y <= 0.0f)
	{
		ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
		resetGyro = true;
	}
	ComputeCrosshairPosition();
	UpdateShooting(DeltaTime);
	UpdatePlayer(DeltaTime);
	UpdateCamera(DeltaTime);
	UpdateDash(DeltaTime);
}

// Called to bind functionality to input
void ALylatPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ALylatPlayerPawn::MoveUpInput);
	PlayerInputComponent->BindAxis("Right", this, &ALylatPlayerPawn::MoveRightInput);
	PlayerInputComponent->BindVectorAxis("Tilt", this, &ALylatPlayerPawn::MovementGyroInput);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ALylatPlayerPawn::ActionDash);
	PlayerInputComponent->BindAction("Dash", IE_Released, this, &ALylatPlayerPawn::ActionStopDash);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ALylatPlayerPawn::ActionShoot);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ALylatPlayerPawn::ActionStopShoot);
	PlayerInputComponent->BindAction("ResetGyro", IE_Pressed, this, &ALylatPlayerPawn::ActionResetGyro);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ALylatPlayerPawn::TouchDown);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ALylatPlayerPawn::TouchDrag);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ALylatPlayerPawn::TouchUp);
}

void ALylatPlayerPawn::DestroyEntity(bool addScore)
{
	//TODO
}

void ALylatPlayerPawn::ComputeCrosshairPosition()
{
	UGameplayStatics::ProjectWorldToScreen((APlayerController*)this->GetController(), oldDir * CrosshairDistance + EntityMesh->GetComponentLocation(), CrosshairPosition);
	CrosshairPosition = FVector2D(FMath::Clamp(CrosshairPosition.X, -50.0f, ViewportSize.X + 50.0f), FMath::Clamp(CrosshairPosition.Y, -50.0f, ViewportSize.Y + 50.0f));
	oldDir = this->EntityMesh->GetForwardVector();
}

void ALylatPlayerPawn::TakeEntityDamage(AActor* entity)
{
	if (Cast<ALylatEntity>(entity))
		EntityLife--;
	if (EntityLife <= 0)
	{
		DestroyEntity();
	}
}

void ALylatPlayerPawn::TakeBulletDamage(ALylatNormalBullet* bullet)
{
	if (bullet->isPlayerSpawned) return;
	EntityLife--;
	if (EntityLife <= 0)
	{
		DestroyEntity();
	}
}