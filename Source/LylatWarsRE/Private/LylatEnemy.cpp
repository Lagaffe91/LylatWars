#include "LylatEnemy.h"

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
	
}

// Called every frame
void ALylatEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (this->IsActivated)
	{
		this->Behaviour(DeltaTime);
	}
}

void ALylatEnemy::Activate()
{
	this->IsActivated = true;
}

int ALylatEnemy::GetScoreAmount()
{
	return 0;
}

void ALylatEnemy::DestroyEntity()
{
	//TODO
	UGameplayStatics::GetGameInstance(GetWorld());
	ALylatEntity::DestroyEntity();
}

