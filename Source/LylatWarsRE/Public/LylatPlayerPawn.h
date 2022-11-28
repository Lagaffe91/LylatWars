// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LylatPlayerPawn.generated.h"

UCLASS()
class LYLATWARSRE_API ALylatPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly)
		class UStaticMeshComponent* PlayerMesh;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly)
		class UStaticMeshComponent* PlayerTrailMesh;

	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		class UCameraComponent* Camera;

	/** Current camera relative position */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		FVector CameraPosition = FVector(-200, 0, 0);

	/** Current camera relative rotation */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		FVector CameraRotation = FVector(0, 0, 0);

	/** Distance from the camera and the player */
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraDistance = -200.0f;

	/** The ration between the center of the screen and the player position when the player moves */
	UPROPERTY(EditAnywhere, Category = Camera)
		float CameraFollowRatio = 0.75f;

	/** Current player relative position */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		FVector PlayerPosition = FVector(0, 0, 0);

	/** Current player relative rotation */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		FVector PlayerRotation = FVector(0, 0, 0);

	/** Player movement space size */
	UPROPERTY(EditAnywhere, Category = Movement)
		FVector2D PlayerPlaneSize = FVector2D(100, 160);

	/** How quickly player will move on the view plane*/
	UPROPERTY(Category = Movement, EditAnywhere)
		float PlayerMaxSpeed = 2.0f;

	/** How quickly player can steer */
	UPROPERTY(Category = Movement, EditAnywhere)
		float PlayerTurnSpeed = 2.0f;

	/** How quickly player will go back to default position */
	UPROPERTY(Category = Movement, EditAnywhere)
		float PlayerUnturnSpeed = 10.0f;

	/** Player trail length factor, depends on speed */
	UPROPERTY(Category = Movement, EditAnywhere)
		float PlayerTrailLength = 1.0f;

	/** Length of the Barrel Roll animation (in seconds) */
	UPROPERTY(Category = Movement, EditAnywhere)
		float BarrelRollLength = 1.0f;

	/** Multiplier for the Barrel Roll animation speed */
	UPROPERTY(Category = Movement, EditAnywhere)
		float BarrelRollSpeed = 1.0f;

	/** Multiplier for the Barrel Roll animation friction */
	UPROPERTY(Category = Movement, EditAnywhere)
		float BarrelRollFriction = 2.0f;

	/** Cooldown for the Barrel Roll animation */
	UPROPERTY(Category = Movement, EditAnywhere)
		float BarrelRollCooldown = 3.0f;

	/**Crosshair position, in the screen space*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = HUD)
		FVector2D CrosshairPosition;

	/**Crosshair distance from camera (in units), keep that high*/
	UPROPERTY(EditAnywhere, Category = HUD, meta = (ClampMin = "0"))
		float CrosshairDistance = 20000;

	// Sets default values for this pawn's properties
	ALylatPlayerPawn();


public :
		void ComputeCrosshairPosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveUpInput(float input);
	void MoveRightInput(float input);
	void MovementGyroInput(FVector value);
	void ActionBarrelRoll();

	void UpdatePlayer(float DeltaTime);
	void UpdateCamera(float DeltaTime);
	void SetupBarrelRollAnim(float DeltaTime);

	FVector2D ViewportSize;
	FVector DefaultTrailSize;
	FVector LastPosition;
	FVector Velocity;
	float BarrelRollAnim = 0.0f;
	float BarrelRollVel = 0.0f;
	float BarrelRollCD = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
