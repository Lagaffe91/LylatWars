#include "LylatEnemy.h"

#include "LylatPlayerPawn.h"
#include "Kismet/GameplayStatics.h"

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
	Super::Tick(DeltaTime);
	
	this->Animate(DeltaTime);

	if (this->IsActivated)
	{
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

int ALylatEnemy::GetScoreAmount()
{
	return 0;
}

void ALylatEnemy::DestroyEntity()
{
	ALylatGameMode* GameMode = dynamic_cast<ALylatGameMode*>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
		GameMode->AddScore(GetScoreAmount());
	ALylatEntity::DestroyEntity();
}

