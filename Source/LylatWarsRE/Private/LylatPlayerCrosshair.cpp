#include "LylatPlayerCrosshair.h"

#include "Components/Image.h"
#include "Components/PanelSlot.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "LylatPlayerPawn.h"
#include "DebugString.h"

ULylatPlayerCrosshair::ULylatPlayerCrosshair(const FObjectInitializer& ObjectInitializer) : UUserWidget(ObjectInitializer)
{
	PlayerPawn = (ALylatPlayerPawn*)UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!PlayerPawn)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, this->GetName() + TEXT(" : Crosshair widget : Failed to retrive player ref"));
	}
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
	UCanvasPanelSlot* slot = Cast<UCanvasPanelSlot>(CrosshairImage->Slot);
	if (!slot)
	{
		DebugError("Canvas Slot is null", 0);
	}
	else
	{
		slot->SetPosition(PlayerPawn->CrosshairPosition);
	}
}