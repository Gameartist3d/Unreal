//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SPCrosshairWidget.h"
#include "SPPlayuurController.generated.h"

/**
 * 
 */
UCLASS()
class SP_API ASPPlayuurController : public APlayerController
{
	GENERATED_BODY()

public:

	//Crosshair widget class
	UPROPERTY(EditAnywhere, Category = Widget)
	TSubclassOf<class USPCrosshairWidget> CrosshairWidgetClass;

	//Ref to crosshair widget
	UPROPERTY(BlueprintReadOnly, Category = Widget)
	class USPCrosshairWidget* CrosshairWidget;

	//property to store the interaction menu widget instance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget)
	class UInteractionMenuWidget* InteractionMenuWidget;

protected:

	virtual void BeginPlay() override;
	
private:
	TSubclassOf<class UUserWidget> DeathScreen;
};
