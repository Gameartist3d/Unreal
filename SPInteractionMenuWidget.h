//3DNomad LLC

#pragma once
//engine includes
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
//SP includes
#include "SPInteractionMenuWidget.generated.h"

struct FInteractableData;
class APlayerCharacter;
class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class SPV1_API USPInteractionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/*Variables*/

	UPROPERTY(VisibleAnywhere, Category = "Interaction | Player")
	APlayerCharacter* PlayerCharacter;


	/*Functions*/
	//Function for updating the Interaction Menu
	void UpdateInteractionMenu(const FInteractableData* InteractableData) const;

protected:
	/*variables*/
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> NameText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ActionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuantityText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> KeypressText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UProgressBar> InteractionProgressBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	float CurrentInteractionDuration = 0.0f;

	/*functions*/

	UFUNCTION()
	float UpdateInteractionProgress();

	/*overrides*/
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
};
