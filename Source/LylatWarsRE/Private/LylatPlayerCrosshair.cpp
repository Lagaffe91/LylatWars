#include "LylatPlayerCrosshair.h"

#include "Components/Image.h"
#include "Components/PanelSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "LylatPlayerPawn.h"
#include "DebugString.h"

ULylatPlayerCrosshair::ULylatPlayerCrosshair(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	PlayerPawn = Cast<ALylatPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

ULylatPlayerCrosshair::~ULylatPlayerCrosshair()
{

}

void ULylatPlayerCrosshair::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
	if (!PlayerPawn)
	{
		DebugError("Player is null", 0);
		return;
	}
	SetPositionInViewport(PlayerPawn->CrosshairPosition);
}