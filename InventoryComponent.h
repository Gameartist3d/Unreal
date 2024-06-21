 //3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FAmmo.h"
#include "FThrowable.h"
#include "ESPCurrency.h"
#include "ESPEquipmentSlot.h"
#include "StatsComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 InventoryLockStrength;

	virtual void BeginPlay() override;

	bool AddItem(class ASPBaseItem* Item);
	bool RemoveItem(class ASPBaseItem* Item);

	//Function for adding UBaseItem to a specific equipment slot
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void EquipSlot(ESPEquipmentSlot SlotToEquip, ASPBaseItem* ItemToEquip);

	//Function for unequipping equipment slot
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void UnEquipSlot(ESPEquipmentSlot SlotToUnEquip);

	//Function for applying Item effects
	UFUNCTION(BlueprintCallable, Category = "Item")
	void ApplyItemEffects(ASPBaseItem* ItemtoUse);

	//Function for removing Item effects
	UFUNCTION(BlueprintCallable, Category = "Item")
	void RemoveItemEffects(ASPBaseItem* ItemToRemove);

	//Tarray of default items that get added to inventory storage
	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class ASPBaseItem*> DefaultItems;

	//Delegate for upadting the inventory 
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	//Delegate for updating slot with ESPEquipmentslot provided
	UPROPERTY(BlueprintAssignable, Category ="Weapon")
	FOnEquipSlotUpdated OnSlotUpdated;

	//Function for adding ammo to the inventory
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void AddAmmo(ESPAmmoName AmmoToAdd, float amount);

	//Function for removing ammo from the inventory
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void RemoveAmmo(ESPAmmoName AmmoToRemove, float amount);

	//Function for adding currency to the inventory
	UFUNCTION(BlueprintCallable, Category = "Currency")
	void AddCurrency(ESPCurrency CurrencyToAdd, float amount);

	//Function for removing currency from the inventory
	UFUNCTION(BlueprintCallable, Category = "Currency")
	void RemoveCurrency(ESPCurrency CurrencyToRemove, float amount);

	//Tarray of items in inventory storage
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<class ASPBaseItem*> InventoryItems;

	//Tmap using the equipment slot as the key and a baseitem as the object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment")
	TMap<ESPEquipmentSlot, ASPBaseItem*> EquippedItems;

	//Tarray of throwable items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<FString, int32> Throwables;

	//Tmap using ammo struct as the key and int32 for the amount of ammo
	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Ammo")
	TMap<ESPAmmoName, float> Ammo;

	//Tmap using currency struct as the key and float for the amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<ESPCurrency, float> Currencies;

		
};
