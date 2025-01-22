//3DNomad LLC

#pragma once
// engine includes
#include "CoreMinimal.h"
// SP includes
#include "Blueprint/UserWidget.h"
#include "MenusWidget.generated.h"

class APlayerCharacter;

/**
 * 
 */
UCLASS()
class SPV1_API UMenusWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	/*variable*/
	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacter;
	/*functions*/
protected:
	/*variables*/
	/*overrides*/
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
};
