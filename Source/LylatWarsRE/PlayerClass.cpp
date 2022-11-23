// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "PlayerClass.h"

// Sets default values
APlayerClass::APlayerClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
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
	PlayerModel->SetRelativeLocation(PlayerPosition);
}

// Called to bind functionality to input
void APlayerClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Forward", this, &APlayerClass::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerClass::MoveRight);

}

void APlayerClass::MoveForward(float value)
{
	PlayerPosition.Z += value;
	PlayerPosition.Z = FMath::Clamp(PlayerPosition.Z, -PlayerMaxHeight, PlayerMaxHeight);
}

void APlayerClass::MoveRight(float value)
{
	PlayerPosition.Y += value;
	PlayerPosition.Y = FMath::Clamp(PlayerPosition.Y, -PlayerMaxWidth, PlayerMaxWidth);
}