#include "LylatEnemy.h"

#include "LylatPlayerPawn.h"
#include "Kismet/GameplayStatics.h"
#include "DebugString.h"

// Sets default values
ALylatEnemy::ALylatEnemy() : ALylatEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALylatEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (ActivtionDelay != 0)
	{
		shouldUpdateDelay = true;
	}

	PlayerReference = (ALylatPlayerPawn*)UGameplayStatics::GetActorOfClass(GetWorld(), ALylatPlayerPawn::StaticClass());
}

// Called every frame
void ALylatEnemy::Tick(float DeltaTime)
{
	this->Animate(DeltaTime);

	if (this->IsActivated)
	{
		Super::Tick(DeltaTime);
		this->Behaviour(DeltaTime);
	}
	else
	{
		if (shouldUpdateDelay && ActivtionDelay > 0)
		{
			ActivtionDelay -= DeltaTime;
		}
		else
		{
			Activate();
		}
	}
}

void ALylatEnemy::Activate()
{
	this->IsActivated = true;
	shouldUpdateDelay = false;
	ActivtionDelay = 0;
}

void ALylatEnemy::Desactivate()
{
	this->IsActivated = false;
}

void ALylatEnemy::TakeEntityDamage(AActor* entity)
{
	if (Cast<ALylatPlayerPawn>(entity))
	{
		EntityLife--;
		Super::TakeEntityDamage(entity);
		if (EntityLife <= 0)
		{
			DestroyEntity();
		}
	}
}