//3DNomad LLC

#pragma once
// engine includes
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
// SP includes
#include "PlayerHUD.generated.h"
//SP forward declarations
struct FInteractableData;
class UMenusWidget;
class USPInteractionMenuWidget;
class USPCrosshairWidget;

/**
 * 
 */
UCLASS()
class SPV1_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	/*Variables*/

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMenusWidget> MenusWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USPInteractionMenuWidget> InteractionMenuWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USPCrosshairWidget> CrosshairWidgetClass;

	UPROPERTY(VisibleAnywhere)
	bool bIsMenusVisible = false;

	/*Functions*/

	APlayerHUD();

	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	void ShowInteractionMenu() const;
	void HideInteractionMenu() const;
	void UpdateInteractionMenu(const FInteractableData* InteractableData) const;

	void ShowCrosshair() const;
	void HideCrosshair() const;
	void UpdateCrosshairTexture(UTexture2D* CrosshairTexture) const;
	void UpdateCrosshairLocation(const FVector2D& Location);

protected:
	/*Variables*/
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMenusWidget> MenusWidget;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USPInteractionMenuWidget> InteractionMenuWidget;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USPCrosshairWidget> CrosshairWidget;

	/*Overrides*/

	virtual void BeginPlay() override;
};
