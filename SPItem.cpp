//3DNomad LLC


#include "SPItem.h"
#include "PlayerCharacter.h"
#include "PlayerInventoryComponent.h"

USPItem::USPItem()
{
}

USPItem* USPItem::CopyItem() const
{
	USPItem* ItemCopy = NewObject<USPItem>(StaticClass());

	ItemCopy->ID = this->ID;
	ItemCopy->ItemQuantity = this->ItemQuantity;
	ItemCopy->ItemCategory = this->ItemCategory;
	ItemCopy->ItemRarity = this->ItemRarity;
	ItemCopy->ItemSlots = this->ItemSlots;
	ItemCopy->ItemTextData = this->ItemTextData;
	ItemCopy->ItemNumericData = this->ItemNumericData;
	ItemCopy->ItemAssetData = this->ItemAssetData;
	ItemCopy->OwningInventory = this->OwningInventory;
	ItemCopy->bIsCopy = true;

	return ItemCopy;
}

void USPItem::ResetItemFlags()
{
	bIsCopy = false;
	bIsPickup = false;
}

void USPItem::SetItemQuantity(const int32 NewQuantity)
{
	if (NewQuantity != this->ItemQuantity)
	{
		ItemQuantity = FMath::Clamp(NewQuantity, 0, this->ItemNumericData.bStackable ? this->ItemNumericData.MaxStackSize : 1);
		if (this->OwningInventory)
		{
			if (this->ItemQuantity <= 0)
			{
				this->OwningInventory->RemoveSingleInstanceOfItem(this);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("USPItem Owning Inventory was null, may be a pickup"));
		}
	}
}

void USPItem::Use(APlayerCharacter* Character)
{
}

void USPItem::UseOnHold(APlayerCharacter* Character)
{
}

