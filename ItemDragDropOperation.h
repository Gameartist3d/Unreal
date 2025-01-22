//3DNomad LLC

#pragma once
//engine includes
#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
//SP includes
#include "ItemDragDropOperation.generated.h"
//SP forward declarations
class UPlayerInventoryComponent;
class USPItem;
/**
 * 
 */
UCLASS()
class SPV1_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	TObjectPtr<USPItem> SourceItem;

	UPROPERTY()
	TObjectPtr<UPlayerInventoryComponent> SourceInventory;
	
};
