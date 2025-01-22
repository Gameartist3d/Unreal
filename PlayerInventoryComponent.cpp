//3DNomad LLC

#include "PlayerInventoryComponent.h"

//SP includes
#include "PlayerCharacter.h"
#include "SPItem.h"

#define DEBUG_TO_SCREEN(Message) GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, FString(__FUNCTION__) + "(" + FString::FromInt(__LINE__) + ") " + Message);

UPlayerInventoryComponent::UPlayerInventoryComponent()
{
	EquippedItems.Add(EItemSlots::MainHand, nullptr);
	EquippedItems.Add(EItemSlots::OffHand, nullptr);
	EquippedItems.Add(EItemSlots::Throwable, nullptr);
	EquippedItems.Add(EItemSlots::Armor, nullptr);
	EquippedItems.Add(EItemSlots::Shield, nullptr);
	EquippedItems.Add(EItemSlots::Pet, nullptr);
}

USPItem* UPlayerInventoryComponent::FindNextItemByID(USPItem* ItemIn) const
{
	if (ItemIn)
	{
		if (const TArray<TObjectPtr<USPItem>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
		{
			return *Result;
		}
	}
	return nullptr;
}


USPItem* UPlayerInventoryComponent::FindMatchingItem(USPItem* ItemIn) const
{
	if (ItemIn)
	{
		if (InventoryContents.Contains(ItemIn))
		{
			return ItemIn;
		}
	}
	return nullptr;
}

USPItem* UPlayerInventoryComponent::FindNextPartialStack(USPItem* ItemIn) const
{
	if (const TArray<TObjectPtr<USPItem>>::ElementType* Result = InventoryContents.FindByPredicate([&ItemIn](const USPItem* InventoryItem)
	{
		return InventoryItem->ID == ItemIn->ID && !InventoryItem->IsItemStackFull();
	}
	))
	{
		return *Result;
	}
	return nullptr;
}

void UPlayerInventoryComponent::RemoveSingleInstanceOfItem(USPItem* ItemToRemove)
{
	InventoryContents.RemoveSingle(ItemToRemove);
	OnInventoryUpdated.Broadcast();
}

int32 UPlayerInventoryComponent::RemoveAmountOfItem(USPItem* ItemIn, int32 AmountToRemove)
{
	const int32 ActualAmountToRemove = FMath::Min(AmountToRemove, ItemIn->ItemQuantity);
	ItemIn->SetItemQuantity(ItemIn->ItemQuantity - ActualAmountToRemove);
	InventoryTotalWeight -= ActualAmountToRemove * ItemIn->GetSingleItemWeight();
	OnInventoryUpdated.Broadcast();
	return ActualAmountToRemove;
}

void UPlayerInventoryComponent::SplitExistingStack(USPItem* ItemIn, const int32 AmountToSplit)
{
	if (InventoryContents.Num() + 1 <= InventorySlotsCapacity)
	{
		RemoveAmountOfItem(ItemIn, AmountToSplit);
		AddNewItem(ItemIn, AmountToSplit);
	}
}

void UPlayerInventoryComponent::EquipItem(USPItem* ItemToEquip, EItemSlots SlotToEquip)
{
	//validate item
	if (ItemToEquip)
	{
		switch (SlotToEquip)
		{
		case EItemSlots::MainHand:
			if (EquippedItems.Contains(SlotToEquip))
			{
				if (USPItem** FoundItem = EquippedItems.Find(SlotToEquip))
				{
					if (*FoundItem != nullptr)
					{
						UnEquipItem(*FoundItem, SlotToEquip);
					}
				}
				EquippedItems.FindOrAdd(SlotToEquip) = ItemToEquip;
				if (APlayerCharacter* PlayerToEquip = Cast<APlayerCharacter>(OwnerCharacter))
				{
					if (ItemToEquip->ItemAssetData.ItemSkeletalMesh != nullptr)
					{
						PlayerToEquip->SetMainHandStaticMVisibility(false);
						PlayerToEquip->SetMainHandSkeletalMesh(ItemToEquip->ItemAssetData.ItemSkeletalMesh);
						PlayerToEquip->SetMainHandSkeletalMVisibility(true);
					}
					else if (ItemToEquip->ItemAssetData.ItemStaticMesh != nullptr)
						{
							PlayerToEquip->SetMainHandSkeletalMVisibility(false);
							PlayerToEquip->SetMainHandStaticMesh(ItemToEquip->ItemAssetData.ItemStaticMesh);
							PlayerToEquip->SetMainHandStaticMVisibility(true);
						}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("Could not resolve MAINHAND item meshes!"));
					}
					PlayerToEquip->bIsMainHandEquipped = true;
					ItemToEquip->bIsEquipped = true;
					
				}
			}
			break;
		case EItemSlots::OffHand:
			if (EquippedItems.Contains(SlotToEquip))
			{
				if (USPItem** FoundItem = EquippedItems.Find(SlotToEquip))
				{
					if (*FoundItem != nullptr)
					{
						UnEquipItem(*FoundItem, SlotToEquip);
					}
				}
				EquippedItems.FindOrAdd(SlotToEquip) = ItemToEquip;
			}
			if (APlayerCharacter* PlayerToEquip = Cast<APlayerCharacter>(OwnerCharacter))
			{
				if (ItemToEquip->ItemAssetData.ItemSkeletalMesh)
				{
					UE_LOG(LogTemp, Error, TEXT("EquippedASkeletonMesh: %s"), *ItemToEquip->ItemAssetData.ItemSkeletalMesh->GetClass()->GetName());
					PlayerToEquip->SetOffHandStaticMVisibility(false);
					PlayerToEquip->SetOffHandSkeletalMesh(ItemToEquip->ItemAssetData.ItemSkeletalMesh);
					PlayerToEquip->SetOffHandSkeletalMVisibility(true);
				}
				else if (ItemToEquip->ItemAssetData.ItemStaticMesh)
				{
					PlayerToEquip->SetOffHandSkeletalMVisibility(false);
					PlayerToEquip->SetOffHandStaticMesh(ItemToEquip->ItemAssetData.ItemStaticMesh);
					PlayerToEquip->SetOffHandStaticMVisibility(true);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("Something is wrong. Equipped item meshes not found."));
				}
				PlayerToEquip->bIsOffHandEquipped = true;
				ItemToEquip->bIsEquipped = true;
			}
			break;
		case EItemSlots::Armor:
			if (EquippedItems.Contains(SlotToEquip))
			{
				if (USPItem** FoundItem = EquippedItems.Find(SlotToEquip))
				{
					if (*FoundItem != nullptr)
					{
						UnEquipItem(*FoundItem, SlotToEquip);
					}
				}
				EquippedItems.FindOrAdd(SlotToEquip) = ItemToEquip;
				ItemToEquip->bIsEquipped = true;
			}
			break;
		case EItemSlots::Shield:
			if (EquippedItems.Contains(SlotToEquip))
			{
				if (USPItem** FoundItem = EquippedItems.Find(SlotToEquip))
				{
					if (*FoundItem != nullptr)
					{
						UnEquipItem(*FoundItem, SlotToEquip);
					}
				}
				EquippedItems.FindOrAdd(SlotToEquip) = ItemToEquip;
				ItemToEquip->bIsEquipped = true;
			}
			break;
		case EItemSlots::Throwable:
			if (EquippedItems.Contains(SlotToEquip))
			{
				if (USPItem** FoundItem = EquippedItems.Find(SlotToEquip))
				{
					if (*FoundItem != nullptr)
					{
						UnEquipItem(*FoundItem, SlotToEquip);
					}
				}
				EquippedItems.FindOrAdd(SlotToEquip) = ItemToEquip;
				if (APlayerCharacter* PlayerToEquip = Cast<APlayerCharacter>(OwnerCharacter))
				{
					PlayerToEquip->bIsThrowableEquipped = true;
					ItemToEquip->bIsEquipped = true;
				}
				
			}
		case EItemSlots::Pet:
			if (EquippedItems.Contains(SlotToEquip))
			{
				if (USPItem** FoundItem = EquippedItems.Find(SlotToEquip))
				{
					if (*FoundItem != nullptr)
					{
						UnEquipItem(*FoundItem, SlotToEquip);
					}
				}
				EquippedItems.FindOrAdd(SlotToEquip) = ItemToEquip;
				ItemToEquip->bIsEquipped = true;
			}
			break;
			
			default:
				UE_LOG(LogTemp, Error, TEXT("EquipItem: Unknown EquipItemSlot"));
			break;
		}
	}
}


void UPlayerInventoryComponent::UnEquipItem(USPItem* ItemToUnEquip, const EItemSlots SlotToUnEquip)
{
	//validate the item
	if (ItemToUnEquip)
	{
		ItemToUnEquip->bIsEquipped = false;

		if (APlayerCharacter* PlayerToEquip = Cast<APlayerCharacter>(OwnerCharacter))
		{
			switch (SlotToUnEquip)
			{
			case EItemSlots::MainHand:
				PlayerToEquip->bIsMainHandEquipped = false;
				PlayerToEquip->SetMainHandSkeletalMVisibility(false);
				PlayerToEquip->SetMainHandStaticMVisibility(false);
				break;

			case EItemSlots::OffHand:
				PlayerToEquip->bIsOffHandEquipped = false;
				PlayerToEquip->SetOffHandSkeletalMVisibility(false);
				PlayerToEquip->SetOffHandStaticMVisibility(false);
				break;

			case EItemSlots::Throwable:
				PlayerToEquip->bIsThrowableEquipped = false;
				PlayerToEquip->SetThrowableStaticMVisibility(false);
				break;

			default:
				break;
			}
		}
	}
}

int32 UPlayerInventoryComponent::CalculateAddedWeightAmount(const USPItem* ItemIn, int32 AmountToAdd) const
{
	const int32 WeightMaxAddAmount = FMath::FloorToInt((GetWeightCapacity() - InventoryTotalWeight) / ItemIn->GetSingleItemWeight());
	if (WeightMaxAddAmount >= AmountToAdd)
	{
		return AmountToAdd;
	}
	return WeightMaxAddAmount;
}

int32 UPlayerInventoryComponent::CalculateNumberForFullStack(const USPItem* StackableItem, int32 InitialRequestedAmount) const
{
	const int32 AddAmountToMakeFullStack = StackableItem->ItemNumericData.MaxStackSize - StackableItem->ItemQuantity;

	return FMath::Min(InitialRequestedAmount, AddAmountToMakeFullStack);
}

FItemAddResult UPlayerInventoryComponent::HandleNonStackableItems(USPItem* ItemIn, int32 AmountToAdd)
{
	//Check if the Item has valid weight
	if (FMath::IsNearlyZero(ItemIn->GetSingleItemWeight()) || ItemIn->GetSingleItemWeight() < 0)
	{
		return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. Item has the invalid weight value."), ItemIn->ItemTextData.ItemName));
	}
	//Check to see if Item weight would exceed the weight capacity
	if (InventoryTotalWeight + ItemIn->GetSingleItemWeight() > GetWeightCapacity())
	{
		return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. Item would exceed weight limit."), ItemIn->ItemTextData.ItemName));

	}

	//Check if adding Item would overflow inventory slot capacity
	if (InventoryContents.Num() + 1 > InventorySlotsCapacity)
	{
		return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. Inventory slot capacity exceeded."), ItemIn->ItemTextData.ItemName));

	}

	AddNewItem(ItemIn, AmountToAdd);
	return FItemAddResult::AllItemsAdded(AmountToAdd, FText::Format(FText::FromString("Added {0} to the inventory."), ItemIn->ItemTextData.ItemName));

}

int32 UPlayerInventoryComponent::HandleStackableItems(USPItem* ItemIn, int32 AmountToAdd)
{
	if (AmountToAdd <= 0 || FMath::IsNearlyZero(ItemIn->GetItemStackWeight()))
	{
		return 0;
	}

	int32 AmountToDistribute = AmountToAdd;
	//check if the input item already exists in the inventory and is not a full stack
	USPItem* ExistingItemStack = FindNextPartialStack(ItemIn);

	while (ExistingItemStack)
	{
		//distribute the item stack over inventory stacks
		if (InventoryContents.Num() + 1 <= InventorySlotsCapacity)
		{

			// calculate how many of the existing item would be needed to make the next full stack
			const int32 AmountToMakeFullStack = CalculateNumberForFullStack(ExistingItemStack, AmountToDistribute);
			//calculate how many of the AmountToMakeFullStack can actually be carried over based on the weight capacity
			const int32 WeightLimitAddAmount = CalculateAddedWeightAmount(ExistingItemStack, AmountToMakeFullStack);

			//check if the remaining amount of items will overflow the weight limit
			if (WeightLimitAddAmount > 0)
			{
				//adjust the existing item stack quantity and inventory total weight
				ExistingItemStack->SetItemQuantity(ExistingItemStack->ItemQuantity + WeightLimitAddAmount);
				InventoryTotalWeight += (ExistingItemStack->GetSingleItemWeight() * WeightLimitAddAmount);

				//adjust the count to be distributed
				AmountToDistribute -= WeightLimitAddAmount;

				ItemIn->SetItemQuantity(AmountToDistribute);

				//if max weight capacity is surpassed by adding item, return early
				if (InventoryTotalWeight + ExistingItemStack->GetSingleItemWeight() > InventoryWeightCapacity)
				{
					OnInventoryUpdated.Broadcast();
					return AmountToAdd - AmountToDistribute;
				}
			}
			else if (WeightLimitAddAmount <= 0)
			{
				if (AmountToDistribute != AmountToAdd)
				{
					// this block will be reached if the weight limit is hit while distributing items across stacks
					OnInventoryUpdated.Broadcast();
					return AmountToAdd - AmountToDistribute;
				}
			
				return 0;
			}

			if (AmountToDistribute <= 0)
			{
				//all items distributed across stacks
				OnInventoryUpdated.Broadcast();
				return AmountToAdd;
			}

			//check if there is a partial stack of the input item
			ExistingItemStack = FindNextPartialStack(ItemIn);
		}
	}
	//no more partial stack, new stack must be made
	if (InventoryContents.Num() + 1 <= InventorySlotsCapacity)
	{
		//check if remaining items can be distributed in the inventory by weight
		const int32 WeightLimitAddAmount = CalculateAddedWeightAmount(ItemIn, AmountToDistribute);

		if (WeightLimitAddAmount > 0)
		{
			//weight limit is reached but there are still items to distribute. . .
			if (WeightLimitAddAmount < AmountToDistribute)
			{
				//adjust the input item and add a new stack 
				AmountToDistribute -= WeightLimitAddAmount;
				ItemIn->SetItemQuantity(AmountToDistribute);
				//create a copy since a partial stack is being added
				AddNewItem(ItemIn->CopyItem(), WeightLimitAddAmount);
				return AmountToAdd - AmountToDistribute;
			}

			//the remainder of the full stack can be added
			AddNewItem(ItemIn, AmountToDistribute);
			return AmountToAdd;
		}
		OnInventoryUpdated.Broadcast();
		return AmountToAdd - AmountToDistribute;
	}
	return 0;
}

FItemAddResult UPlayerInventoryComponent::HandleAddItem(USPItem* NewItem)
{
	if (GetOwner())
	{
		//Handle non-stackable items
		const int32 InitialRequestedAddAmount = NewItem->ItemQuantity;
		if (!NewItem->ItemNumericData.bStackable)
		{
			return HandleNonStackableItems(NewItem, InitialRequestedAddAmount);
		}

		//Handle stackable items
		const int32 StackableAmountAdded = HandleStackableItems(NewItem, InitialRequestedAddAmount);

		if (StackableAmountAdded == InitialRequestedAddAmount)
		{
			return FItemAddResult::AllItemsAdded(InitialRequestedAddAmount, FText::Format(FText::FromString("Successfully added {0} {1} to the inventory."), InitialRequestedAddAmount, NewItem->ItemTextData.ItemName));
		}

		if (StackableAmountAdded < InitialRequestedAddAmount && StackableAmountAdded > 0)
		{
			return FItemAddResult::AddedPartial(StackableAmountAdded, FText::Format(FText::FromString("Partial amount of {0} added to the inventory. Number added = {1}"), NewItem->ItemTextData.ItemName, StackableAmountAdded));
		}

		if (StackableAmountAdded <= 0)
		{
			return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could not add {0} to the inventory. No slots left or invalid item."), NewItem->ItemTextData.ItemName));
		}
	}
	check(false);
	return FItemAddResult::AddedNone(FText::FromString(TEXT("GetOwner() check failed. Add Item failure.")));
}

void UPlayerInventoryComponent::AddNewItem(USPItem* Item, const int32 AmountToAdd)
{
	USPItem* NewItem;

	if (Item->bIsCopy || Item->bIsPickup)
	{
		// if the item is a copy or a world pickup
		NewItem = Item;
		NewItem->ResetItemFlags();
	}
	else
	{
		//for item split cases
			NewItem = Item->CopyItem();
		}

		NewItem->OwningInventory = this;
		NewItem->SetItemQuantity(AmountToAdd);

		InventoryContents.Add(NewItem);
		InventoryTotalWeight += NewItem->GetItemStackWeight();
		OnInventoryUpdated.Broadcast();
}
