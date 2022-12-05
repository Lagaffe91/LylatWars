// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LylatEntity.h"
#include "LylatEventTrigger.generated.h"

UCLASS()
class LYLATWARSRE_API ALylatEventTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALylatEventTrigger();

	UPROPERTY(Category = "Lylat Event Trigger", EditAnywhere, BlueprintReadWrite)
		TArray<AActor*> eventParameters;

	/**UBoxComponent representing the hitbox of the entity**/
	UPROPERTY(Category = "Lylat Event Trigger", VisibleAnywhere, BlueprintReadOnly)
		class UBoxComponent* EventHitbox;

	/**True if the event have already been triggered*/
	UPROPERTY(Category = "Lylat Event Trigger", VisibleAnywhere, BlueprintReadOnly)
		bool EventIsTriggered = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void HitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**This function will be called when the trigger is triggered"*/
	UFUNCTION(BlueprintNativeEvent, Category = "Lylat Event Trigger")
		void ResolveEvent();
	virtual void ResolveEvent_Implementation();
};
