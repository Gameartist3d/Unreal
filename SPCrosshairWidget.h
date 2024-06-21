//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/UserWidget.h"
#include "SPCrosshairWidget.generated.h"

/**
 * 
 */

UCLASS()
class SP_API USPCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//Tmap of crosshair names and textures
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Blueprintable, Category = Widget)
	TMap<FName, UTexture2D*> CrosshairTextures;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Crosshair")
	void SetCrosshairTexture(FName crosshairname);
};
 
