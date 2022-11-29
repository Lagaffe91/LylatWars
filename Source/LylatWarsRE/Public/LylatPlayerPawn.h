// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LylatNormalBullet.h"

#include "LylatEntity.h"
#include "LylatPlayerPawn.generated.h"

UCLASS(Blueprintable)
class LYLATWARSRE_API ALylatPlayerPawn : public ALylatEntity
{
	GENERATED_BODY()

public:
	UPROPERTY(Category = "Lylat Player", VisibleDefaultsOnly, BlueprintReadOnly)
		class UStaticMeshComponent* PlayerTrailMesh;

	UPROPERTY(Category = "Lylat Player|Camera", VisibleDefaultsOnly, BlueprintReadOnly)
		class UCameraComponent* Camera;

	/** Current camera relative position */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lylat Player|Camera")
		FVector CameraPosition = FVector(-200, 0, 0);

	/** Current camera relative rotation */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lylat Player|Camera")
		FVector CameraRotation = FVector(0, 0, 0);

	/** Distance from the camera and the player */
	UPROPERTY(EditAnywhere, Category = "Lylat Player|Camera")
		float CameraDistance = -200.0f;

	/** The ratio between the center of the screen and the player position when the player moves */
	UPROPERTY(EditAnywhere, Category = "Lylat Player|Camera")
		float CameraFollowRatio = 0.75f;

	/** Current player relative position */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement")
		FVector PlayerPosition = FVector(0, 0, 0);

	/** Current player relative rotation */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement")
		FVector PlayerRotation = FVector(0, 0, 0);

	/** Player movement space size */
	UPROPERTY(EditAnywhere, Category = "Lylat Player|Mouvement")
		FVector2D PlayerPlaneSize = FVector2D(100, 160);

	/** How quickly player will move on the view plane*/
	UPROPERTY(EditAnywhere, Category = "Lylat Player|Mouvement")
		float PlayerMaxSpeed = 2.0f;

	/** How quickly player can steer */
	UPROPERTY(Category = Movement, EditAnywhere)
		float PlayerTurnSpeed = 2.0f;

	/** How quickly player will go back to default position */
	UPROPERTY(EditAnywhere, Category = "Lylat Player|Mouvement")
		float PlayerUnturnSpeed = 10.0f;

	/** Player trail length factor, depends on speed */
	UPROPERTY(EditAnywhere, Category = "Lylat Player|Mouvement")
		float PlayerTrailLength = 1.0f;

	/** Speed of the Barrel Roll animation in seconds */
	UPROPERTY(Category = "Lylat Player|Mouvement", EditAnywhere)
		float BarrelRollSpeed = 0.5f;

	/** Cooldown for the Barrel Roll animation */
	UPROPERTY(Category = "Lylat Player|Mouvement", EditAnywhere)
		float BarrelRollCooldown = 0.0f;

	/** Cooldown for the shooting rate */
	UPROPERTY(Category = Movement, EditAnywhere)
		float ShootCooldown = 0.2f;

	/**Crosshair position, in the screen space*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lylat Player|HUD")
		FVector2D CrosshairPosition;

	/**Crosshair distance from camera (in units), keep that high*/
	UPROPERTY(EditAnywhere, Category = "Lylat Player|HUD", meta = (ClampMin = "0"))
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
	void TouchDown(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchDrag(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchUp(ETouchIndex::Type FingerIndex, FVector Location);
	void ActionShoot();
	void ActionStopShoot();
	void ActionBarrelRoll(bool reversed);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void ActionDash();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void ActionResetGyro();

	void UpdateShooting(float DeltaTime);
	void UpdatePlayer(float DeltaTime);
	void UpdateCamera(float DeltaTime);
	void SetupBarrelRollAnim(float DeltaTime);

	FVector2D ViewportSize;
	FVector DefaultTrailSize;
	FVector LastPosition;
	FVector Velocity;
	float BarrelRollAnim = 0.0f;
	float BarrelRollCD = 0.0f;
	float ShootCD = 0.0f;
	bool resetGyro = true;
	bool isTouched = false;
	bool isShooting = false;
	bool barrelReversed = false;
	FVector2D touchStart;
	FVector2D touchLast;
	FVector2D touchCurrent;
	FVector2D touchVel;
	FVector oldDir;
	FQuat defaultRotation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
