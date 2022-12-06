// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LylatNormalBullet.h"
#include "LylatBombBullet.h"
#include "LylatGameInstance.h"
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

	/**Bomb shot by the player, aka the nuke, aka the big boom, aka the thing that does quite a lot of damage*/
	UPROPERTY(Category = "Lylat Player|Weapons", EditAnywhere, BlueprintReadOnly)
		TSubclassOf<ALylatBombBullet> BombBulletType;

	/** The amount of bombs (nukes) the player has at most*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lylat Player|Weapons", meta = (ClampMin = "0"))
		int BombMaxCount = 3;

	/** The current amount of bombs the current player currently has in its current inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lylat Player|Weapons", meta = (ClampMin = "0"))
		int BombCount = 3;

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

	/**True if the player is dashing*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement|Dash")
		bool IsDashing = false;

	/**Current speed applied on the rail by the dash action*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement|Dash")
		float DashSpeed = 0;

	/**Extra speed given by the dash*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement|Dash", meta = (ClampMin = "0"))
		float DashMaxSpeed = 2;

	/**Higer value mean it will reach it's max value quicker*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement|Dash", meta = (ClampMin = "0"))
		float DashAcceleration = 1;

	/**Deceleration higher mean quicker lerp after the end of a dash*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement|Dash", meta = (ClampMin = "0"))
		float DashDeceleration = 1;

	/**Value between 1 and 0, represent the dash gauge*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement|Dash")
		float DashGauge = 1;

	/**Cost of the dash, higher value mean less dash time*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement|Dash", meta = (ClampMin = "0"))
		float DashDrain = 1;

	/**Regeneration of the dash, higher value mean quicker recovery*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement|Dash", meta = (ClampMin = "0"))
		float DashRegeneration = 1;

	/**Minial power left in the gauge necessary to start a dash (between 0 and 1)*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement|Dash", meta = (ClampMin = "0", ClampMax = "1"))
		float DashInitialCost = 0.1;

	/**Time (in seconds) the player have been dashing for*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement|Dash")
		float DashTimer = 0;

	/**Time (in seconds) the player have been dashing for*/
	UPROPERTY(BlueprintReadOnly, Category = "Lylat Player|Mouvement|Dash")
		float DashDecelerationTimer = 0;

	/**Reference to the rail the player is on (null otherwise)*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lylat Player|Mouvement|Dash")
	class ALylatPlayerRail* PlayerRail;

	/**Extra bonus super ultra mega bomb sound*/
	UPROPERTY(Category = "Lylat Entity", EditAnywhere, BlueprintReadOnly)
	UAudioComponent* BombSound = nullptr;

	// Sets default values for this pawn's properties
	ALylatPlayerPawn();


public :
		void ComputeCrosshairPosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveUpInput(float input);
	void MoveRightInput(float input);
	void MovementGyroInput(float deltaTime);
	void TouchDown(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchDrag(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchUp(ETouchIndex::Type FingerIndex, FVector Location);
	void ActionShoot();
	void ActionStopShoot();
	void ActionBarrelRoll(bool reversed);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void ActionDash();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void ActionStopDash();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void ActionResetGyro();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void ActionUseBomb();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Lylat Player|Events")
		void PauseEvent();
	void PauseEvent_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Lylat Player|Events")
		void DeathEvent();
	void DeathEvent_Implementation();

	void UpdateDash(float DeltaTime);
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
	FVector2D gyroInput;
	FVector oldDir;
	FVector defaultPlayerPos;
	FVector defaultPlayerRot;
	ULylatGameInstance* instance = nullptr;

	/**Security to avoid weird deceleration behaviour*/
	bool DashShouldDecelerate = false;
	float DashMaxSpeedAtteigned = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void TakeEntityDamage(AActor* entity) override;

	virtual void TakeBulletDamage(ALylatNormalBullet* bullet, int amount = 1) override;

	virtual void DestroyEntity(bool addScore = true);
};
