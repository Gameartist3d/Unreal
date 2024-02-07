#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FAmmo.h"
#include "FThrowable.h"
#include "FCurrency.h"
#include "InventoryComponent.generated.h"

//For updating the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponSlotUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 InventoryCapacity;

	virtual void BeginPlay() override;

	bool AddItem(class UBaseItem* Item);
	bool RemoveItem(class UBaseItem* Item);
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void EquipWeapon(class UWeaponItem* WeaponSlot, class UWeaponItem* newWeapon);
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UnEquipWeapon(class UWeaponItem* WeaponSlot);

	UPROPERTY(EditDefaultsOnly, Instanced)
	TArray<class UBaseItem*> DefaultItems;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UPROPERTY(BlueprintAssignable, Category ="Weapon")
	FOnWeaponSlotUpdated OnWeaponSlotUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<class UBaseItem*> InventoryItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	class UShieldItem* Shield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	class UArmorItem* Armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UWeaponItem* WeaponSlot1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UWeaponItem* WeaponSlot2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	class UWeaponItem* NewWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FThrowable> Throwables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FAmmo> AmmoTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FCurrency> Currencies;

		
};
