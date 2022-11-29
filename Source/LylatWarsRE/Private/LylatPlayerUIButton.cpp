#include "LylatPlayerUIButton.h"

#include "Kismet/GameplayStatics.h"
#include "DebugString.h"

ULylatPlayerUIButton::ULylatPlayerUIButton(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	PlayerPawn = Cast<ALylatPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}