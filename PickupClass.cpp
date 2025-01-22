//3DNomad LLc

#include "PickupClass.h"

#include "PlayerCharacter.h"
#include "PlayerInventoryComponent.h"
#include "SPItem.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickupClass::APickupClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickupMesh->SetSimulatePhysics(true);
	SetRootComponent(PickupMesh);

}

// Called when the game starts or when spawned
void APickupClass::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup(ItemQuantity);
	
}

void APickupClass::InitializePickup(const int32 InQuantity)
{
	if (!ItemRowHandle.IsNull())
	{
		const FItemData* ItemDataRef = ItemRowHandle.GetRow<FItemData>(ItemRowHandle.RowName.ToString());
		ItemReference = NewObject<USPItem>(this, USPItem::StaticClass());
		if (!ItemReference)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create Pickup Item"));
			return;
		}

		ItemReference->ID = ItemDataRef->ID;
		ItemReference->ItemCategory = ItemDataRef->ItemCategory;
		ItemReference->ItemRarity = ItemDataRef->ItemRarity;
		ItemReference->ItemSlots = ItemDataRef->ItemSlots;
		ItemReference->ItemTextData = ItemDataRef->ItemTextData;
		ItemReference->ItemNumericData = ItemDataRef->ItemNumericData;
		ItemReference->ItemAssetData = ItemDataRef->ItemAssetData;

		ItemReference->ItemNumericData.bStackable = ItemDataRef->ItemNumericData.MaxStackSize > 1;
		InQuantity <= 0 ? ItemReference->SetItemQuantity(1) : ItemReference->SetItemQuantity(InQuantity);
		PickupMesh->SetStaticMesh(ItemDataRef->ItemAssetData.ItemStaticMesh);
		UpdateInteractableData();
	}
}

void APickupClass::InitializeDrop(USPItem* DropItem, const int32 DropQuantity)
{
	ItemReference = DropItem;

	ItemReference->ItemNumericData.bStackable = DropItem->ItemNumericData.bStackable;
	DropQuantity <= 0 ? ItemReference->SetItemQuantity(1) : ItemReference->SetItemQuantity(DropQuantity);
	ItemReference->OwningInventory = nullptr;
	PickupMesh->SetStaticMesh(DropItem->ItemAssetData.ItemStaticMesh);
	UpdateInteractableData();

}

void APickupClass::BeginFocus()
{
	if (PickupMesh)
	{
		PickupMesh->SetRenderCustomDepth(true);
	}
}

void APickupClass::EndFocus()
{
	if (PickupMesh)
	{
		PickupMesh->SetRenderCustomDepth(false);
	}
}

void APickupClass::Interact(APlayerCharacter* Character)
{
	if(Character)
	{
		TakePickup(Character);
	}
}

void APickupClass::UpdateInteractableData()
{
	InstanceInteractableData.InteractionType = EInteractionType::Item;
	InstanceInteractableData.InteractionName = ItemReference->ItemTextData.InteractionName;
	InstanceInteractableData.InteractableActorName = ItemReference->ItemTextData.ItemName;
	InstanceInteractableData.Quantity = ItemReference->ItemQuantity;
	InteractableData = InstanceInteractableData;
}

void APickupClass::TakePickup(const APlayerCharacter* Taker)
{
		if (!IsPendingKillPending())
		{
			if (ItemReference)
			{
				if(UPlayerInventoryComponent* PlayerInventory = Taker->GetInventory())
				{
					const FItemAddResult AddResult = PlayerInventory->HandleAddItem(ItemReference);

					switch (AddResult.OperationResult)
					{
					case EItemAddResult::IAR_NoItemAdded:
						break;
					case EItemAddResult::IAR_PartialAmountAdded:
						UpdateInteractableData();
						Taker->UpdateInteractionWidget();
						break;
					case EItemAddResult::IAR_AllItemsAdded:
						Destroy();
						break;
					default:
						break;
					}
					UE_LOG(LogTemp, Warning, TEXT("%s"), *AddResult.ResultMessage.ToString());
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("ERROR: Player Inventory Component is null -_-"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Pickup Item was null! Internal System level error warning!"));
			}
		}
	
}

#if WITH_EDITOR
void APickupClass::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(FDataTableRowHandle, RowName))
	{
		if (!ItemRowHandle.IsNull())
		{
			const FItemData* ItemData = ItemRowHandle.GetRow<FItemData>(ItemRowHandle.RowName.ToString());
			PickupMesh->SetStaticMesh(ItemData->ItemAssetData.ItemStaticMesh);
		}
	}
}
#endif
