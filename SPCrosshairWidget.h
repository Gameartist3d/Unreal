//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPCrosshairWidget.generated.h"

/**
 * 
 */
UCLASS()
class SPV1_API USPCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/*variables*/

	//Crosshair Texture
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Crosshair")
	UTexture2D* CrosshairTexture;

};
