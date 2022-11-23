#include "PlayerClass.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Input/Events.h"
#include "DebugString.h"

// Sets default values
APlayerClass::APlayerClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(RootComponent); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->SetRelativeLocationAndRotation(CameraPosition, FQuat::MakeFromEuler(CameraRotation));
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PlayerModel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerModel"));
	PlayerModel->SetupAttachment(RootComponent);
	PlayerModel->SetRelativeLocationAndRotation(PlayerPosition, FQuat::MakeFromEuler(PlayerRotation));
	PlayerModel->SetRelativeScale3D(FVector(0.1f,0.1f,0.1f));

	GetCharacterMovement()->GravityScale = 0.0f;
}

// Called when the game starts or when spawned
void APlayerClass::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerRotation = PlayerRotation * (1 - 5.0 * DeltaTime);
	PlayerModel->SetRelativeLocationAndRotation(PlayerPosition, FQuat::MakeFromEuler(PlayerRotation));
}

// Called to bind functionality to input
void APlayerClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &APlayerClass::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerClass::MoveRight);

	PlayerInputComponent->BindVectorAxis("Tilt", this, &APlayerClass::TiltMovement);


}

void APlayerClass::MoveForward(float value)
{
	PlayerPosition.Z += value;
	PlayerRotation.Y += value;
	PlayerPosition.Z = FMath::Clamp(PlayerPosition.Z, -PlayerMaxHeight, PlayerMaxHeight);
}

void APlayerClass::MoveRight(float value)
{
	PlayerPosition.Y += value;
	PlayerRotation.Z += value;
	PlayerPosition.Y = FMath::Clamp(PlayerPosition.Y, -PlayerMaxWidth, PlayerMaxWidth);
}

void APlayerClass::TiltMovement(FVector value)
{
	Debug("%.2f %.2f %.2f", value.X, value.Y, value.Z);
}