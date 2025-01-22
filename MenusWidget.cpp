//3DNomad LLC

//Sp includes
#include "MenusWidget.h"
#include "ItemDragDropOperation.h"
#include "PlayerCharacter.h"
#include "SPItem.h"

void UMenusWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UMenusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn());
}

bool UMenusWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	if(PlayerCharacter && ItemDragDrop->SourceItem)
	{
		PlayerCharacter->DropItem(ItemDragDrop->SourceItem, ItemDragDrop->SourceItem->ItemQuantity);
		return true;
	}
	return false;

}
