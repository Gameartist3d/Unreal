//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemData.h"
#include "SPItem.generated.h"

class APlayerCharacter;
class UPlayerInventoryComponent;

/**
 * 
 */

UCLASS()
class SPV1_API USPItem : public UObject
{

	GENERATED_BODY()

public:

	/*Variables*/

	//Reference variable to the owning inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SPItem")
	TObjectPtr<UPlayerInventoryComponent> OwningInventory;

	UPROPERTY(VisibleAnywhere, Category = "SPItem")
	FName ID = TEXT("ID");
	
	UPROPERTY(VisibleAnywhere, Category = "SPItem")
	EItemCategory ItemCategory = EItemCategory::Misc;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	EItemRarity ItemRarity = EItemRarity::Common;

	//TArray of ItemSlots this item can be equipped to
	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	TArray<EItemSlots> ItemSlots;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	FItemTextData ItemTextData;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	FItemNumericData ItemNumericData;

	UPROPERTY(VisibleAnywhere, Category = "ItemData")
	FItemAssetData ItemAssetData;

	//Variable to track the stack amount of this item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SPItem")
	int32 ItemQuantity = 1;

	//Bool to determine if this instance is a copy
	bool bIsCopy = false;

	//Bool to determine if this instance is a pickup
	bool bIsPickup = false;

	//Bool for indicating that this item is equipped
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
	bool bIsEquipped = false;
	
	/*Functions*/

	//Ya know what it is
	USPItem();

	//Function for copying self to new item
	UFUNCTION(BlueprintCallable, Category = "SPItem")
	USPItem* CopyItem() const;

	//Function for resetting the bool flags for bIsCopy&&bIsPickup
	void ResetItemFlags();

	//Functions for getting Item/Item Stack weight
	FORCEINLINE float GetItemStackWeight() const {return ItemQuantity * ItemNumericData.Weight; };
	FORCEINLINE float GetSingleItemWeight() const {return ItemNumericData.Weight; };
	
	//Function to check if the stack is full
	UFUNCTION(Category = "SPItem")
	FORCEINLINE bool IsItemStackFull() const { return ItemQuantity == ItemNumericData.MaxStackSize;  };

	//Function for setting the quantity of this item
	UFUNCTION(BlueprintCallable, Category = "SPItem")
	void SetItemQuantity(const int32 NewQuantity);

	//Function for using this item
	UFUNCTION(BlueprintCallable, Category = "SPItem")
	virtual void Use(APlayerCharacter* Character);

	//Function for using this item's hold function
	UFUNCTION(BlueprintCallable, Category = "SPItem")
	virtual void UseOnHold(APlayerCharacter* Character);

	/*Overrides*/

protected:
	/*variables*/
	
	/*functions*/

protected:
	bool operator==(const FName& OtherID) const
	{
		return this->ID == OtherID;
	}
};
