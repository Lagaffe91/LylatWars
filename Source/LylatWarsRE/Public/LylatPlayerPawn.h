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

	// Sets default values for this pawn's properties
	ALylatPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveUpInput(float input);
	void MoveRightInput(float input);
	void MovementTiltInput(FVector value);

	FVector2D ViewportSize;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
