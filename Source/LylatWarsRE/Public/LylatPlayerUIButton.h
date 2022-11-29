#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LylatPlayerPawn.h"
#include "LylatPlayerUIButton.generated.h"

/**
 * 
 */
UCLASS()
class LYLATWARSRE_API ULylatPlayerUIButton : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ALylatPlayerPawn* PlayerPawn;

	ULylatPlayerUIButton(const FObjectInitializer& ObjectInitializer);
private:

	
};
