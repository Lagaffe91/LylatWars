#include "LylatPlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"	

#include "DebugString.h"

// Sets default values
ALylatPlayerPawn::ALylatPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	USceneComponent* base = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerShipMesh"));
	PlayerMesh->SetRelativeLocationAndRotation(PlayerPosition, FQuat::MakeFromEuler(PlayerRotation));
	PlayerMesh->SetupAttachment(base);

	PlayerTrailMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerShipTrailMesh"));
	PlayerTrailMesh->SetupAttachment(PlayerMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraPosition.X = CameraDistance;
	Camera->SetRelativeLocationAndRotation(CameraPosition, FQuat::MakeFromEuler(CameraRotation));
	Camera->SetupAttachment(base);
	Camera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void ALylatPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	DefaultTrailSize = PlayerTrailMesh->GetRelativeScale3D();
	LastPosition = GetActorLocation();
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
	if (resetGyro)
	{
		defaultRotation = FQuat::MakeFromEuler(value).Inverse();
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
			Velocity.Y += axis.Y * PlayerMaxSpeed * 70.0f;
			Velocity.Z += axis.Z * PlayerMaxSpeed * -70.0f;
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

void ALylatPlayerPawn::ActionBarrelRoll(bool reversed)
{
	if (BarrelRollCD > 0.0f) return;
	barrelReversed = reversed;
	BarrelRollAnim = BarrelRollLength;
	BarrelRollCD = BarrelRollCooldown;
}

void ALylatPlayerPawn::ActionDash()
{
	Debug("Dash",0);
}

void ALylatPlayerPawn::ActionResetGyro()
{
	resetGyro = true;
}

void ALylatPlayerPawn::UpdatePlayer(float DeltaTime)
{
	SetupBarrelRollAnim(DeltaTime);
	PlayerRotation.X += BarrelRollVel * DeltaTime;
	PlayerRotation.X = FMath::Fmod(PlayerRotation.X, 360.0f);
	if (PlayerRotation.X < -180.0f) PlayerRotation.X += 360.0f;
	if (PlayerRotation.X > 180.0f) PlayerRotation.X -= 360.0f;
	Velocity = FVector::ZeroVector;
	PlayerPosition.Y = FMath::Clamp(PlayerPosition.Y, -PlayerPlaneSize.X / 2, PlayerPlaneSize.X / 2);
	PlayerPosition.Z = FMath::Clamp(PlayerPosition.Z, -PlayerPlaneSize.Y / 2, PlayerPlaneSize.Y / 2);
	float rotationX = PlayerRotation.X;
	PlayerRotation = PlayerRotation * (1 - PlayerUnturnSpeed * DeltaTime);
	PlayerRotation.X = rotationX;
	PlayerMesh->SetRelativeLocationAndRotation(PlayerPosition, FQuat::MakeFromEuler(PlayerRotation + FVector(PlayerRotation.Z * 0.5f, PlayerPosition.Z / PlayerPlaneSize.Y * 40, PlayerPosition.Y / PlayerPlaneSize.X * 80)));
}

void ALylatPlayerPawn::UpdateCamera(float DeltaTime)
{
	CameraPosition.X = CameraDistance;
	CameraPosition.Z = PlayerPosition.Z * CameraFollowRatio + (1 - CameraFollowRatio) * (PlayerPosition.Z / PlayerPlaneSize.Y * 2.0f) * (CameraDistance * (ViewportSize.Y / ViewportSize.X) + PlayerPlaneSize.Y * 0.5f);
	CameraPosition.Y = PlayerPosition.Y * CameraFollowRatio + (1 - CameraFollowRatio) * (PlayerPosition.Y / PlayerPlaneSize.X * 2.0f) * (CameraDistance + PlayerPlaneSize.X * 0.5f);
	Camera->SetRelativeLocation(CameraPosition);
	FVector Position = GetActorLocation();
	float length = PlayerTrailLength * (Position - LastPosition).Size() / DeltaTime;
	length = FMath::Clamp(length, 0.001f, 50.0f);
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
	Velocity = Velocity.GetClampedToMaxSize(PlayerMaxSpeed);
	BarrelRollCD -= DeltaTime;
	PlayerPosition += Velocity * DeltaTime;
	PlayerRotation.Y += Velocity.Z * DeltaTime * PlayerTurnSpeed;
	PlayerRotation.Z += Velocity.Y * DeltaTime * PlayerTurnSpeed;
	if (BarrelRollAnim <= 0.0f)
	{
		BarrelRollVel = BarrelRollVel * (1 - BarrelRollFriction * DeltaTime) + FMath::FindDeltaAngleDegrees(PlayerRotation.X, 0.0f) * DeltaTime * BarrelRollSpeed * 0.1f;
	}
	else
	{
		BarrelRollVel += BarrelRollSpeed * DeltaTime * (barrelReversed ? -1.0f : 1.0f);
		BarrelRollAnim -= DeltaTime;
	}
}

// Called every frame
void ALylatPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ViewportSize.X <= 0.0f || ViewportSize.Y <= 0.0f)
	{
		ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	}
	ComputeCrosshairPosition();
	UpdatePlayer(DeltaTime);
	UpdateCamera(DeltaTime);
}

// Called to bind functionality to input
void ALylatPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ALylatPlayerPawn::MoveUpInput);
	PlayerInputComponent->BindAxis("Right", this, &ALylatPlayerPawn::MoveRightInput);
	PlayerInputComponent->BindVectorAxis("Tilt", this, &ALylatPlayerPawn::MovementGyroInput);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ALylatPlayerPawn::ActionDash);
	PlayerInputComponent->BindAction("ResetGyro", IE_Pressed, this, &ALylatPlayerPawn::ActionResetGyro);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ALylatPlayerPawn::TouchDown);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ALylatPlayerPawn::TouchDrag);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ALylatPlayerPawn::TouchUp);
}

void ALylatPlayerPawn::ComputeCrosshairPosition()
{
	UGameplayStatics::ProjectWorldToScreen((APlayerController*)this->GetController(), oldDir * CrosshairDistance + this->GetActorLocation() + this->PlayerPosition - this->CameraPosition, CrosshairPosition);
	CrosshairPosition = FVector2D(FMath::Clamp(CrosshairPosition.X, -50.0f, ViewportSize.X + 50.0f), FMath::Clamp(CrosshairPosition.Y, -50.0f, ViewportSize.Y + 50.0f));
	oldDir = this->PlayerMesh->GetForwardVector();
}