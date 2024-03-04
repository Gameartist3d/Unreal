//3DNomad LLC


#include "InventoryComponent.h"
#include "BaseItem.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	InventoryCapacity = 100;

}
	// Called when the game starts
	void UInventoryComponent::BeginPlay()
	{
		Super::BeginPlay();

		for (auto& Item : DefaultItems) {
			AddItem(Item);
		}

		// ...

	}

	bool UInventoryComponent::AddItem(UBaseItem* Item)
	{
		if (InventoryItems.Num() >= InventoryCapacity || !Item) {
			return false;
		}
		Item->OwnerInventory = this;
		Item->World = GetWorld();
		InventoryItems.Add(Item);

		//Update UI
		OnInventoryUpdated.Broadcast();
		return true;
	}

	bool UInventoryComponent::RemoveItem(UBaseItem* Item)
	{
		if (Item) {
			Item->OwnerInventory = nullptr;
			Item->World = nullptr;
			InventoryItems.RemoveSingle(Item);
			OnInventoryUpdated.Broadcast();
			return true;

		}
		return false;
	}

	void UInventoryComponent::EquipSlot(ESPEquipmentSlot SlotToEquip, UBaseItem* ItemToEquip)
	{
		if (ItemToEquip->ItemSlots.Contains(SlotToEquip))
		{
			if (EquippedItems.Contains(SlotToEquip))
			{
				UnEquipSlot(SlotToEquip);
			}

			EquippedItems.Add(SlotToEquip, ItemToEquip);

			ApplyItemEffects(ItemToEquip);

			OnSlotUpdated.Broadcast(SlotToEquip);
		}
	}

	void UInventoryComponent::UnEquipSlot(ESPEquipmentSlot SlotToUnEquip)
	{
		if (EquippedItems.Contains(SlotToUnEquip))
		{
			EquippedItems.Remove(SlotToUnEquip);
			OnSlotUpdated.Broadcast(SlotToUnEquip);
		}
	}

	void UInventoryComponent::ApplyItemEffects(UBaseItem* ItemtoUse)
	{

	}


