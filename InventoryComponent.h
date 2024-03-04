//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FAmmo.h"
#include "FThrowable.h"
#include "FCurrency.h"
#include "ESPEquipmentSlot.h"
#include "InventoryComponent.generated.h"

//For updating the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipSlotUpdated, ESPEquipmentSlot, SlotChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	//Total capacity for this inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 InventoryCapacity;

	virtual void BeginPlay() override;

	bool AddItem(class UBaseItem* Item);
	bool RemoveItem(class UBaseItem* Item);

	//Function for adding UBaseItem to a specific equipment slot
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void EquipSlot(ESPEquipmentSlot SlotToEquip, UBaseItem* ItemToEquip);

	//Function for unequipping equipment slot
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void UnEquipSlot(ESPEquipmentSlot SlotToUnEquip);

	//Function for applying Item effects
	UFUNCTION(BlueprintCallable, Category = "Item")
	void ApplyItemEffects(UBaseItem* ItemtoUse);

	//Tarray of default items that get added to inventory storage
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UBaseItem*> DefaultItems;

	//Delegate for upadting the inventory 
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	//Delegate for updating slot with ESPEquipmentslot provided
	UPROPERTY(BlueprintAssignable, Category ="Weapon")
	FOnEquipSlotUpdated OnSlotUpdated;

	//Tarray of items in inventory storage
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<class UBaseItem*> InventoryItems;

	//Tmap using the equipment slot as the key and a baseitem as the object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<ESPEquipmentSlot, UBaseItem*> EquippedItems;

	//Tarray of throwable items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FThrowable> Throwables;

	//Tmap using ammo struct as the key and int32 for the amount of ammo
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Ammo")
	TArray<FAmmo> Ammo;

	//Tmap using currency struct as the key and float for the amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FCurrency> Currencies;

		
};
