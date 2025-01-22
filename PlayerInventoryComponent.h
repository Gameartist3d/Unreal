//3DNomad LLC

#pragma once
// engine includes
#include "CoreMinimal.h"
// SP includes
#include "BaseInventoryComponent.h"
#include "FAmmo.h"
#include "FCurrency.h"
#include "PlayerInventoryComponent.generated.h"

enum class EItemSlots : uint8;
DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated)

class USPItem;

UENUM(BlueprintType)
enum class EItemAddResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName = "No Item Added"),
	IAR_PartialAmountAdded UMETA(DisplayName = "Partial Amount Added"),
	IAR_AllItemsAdded UMETA(DisplayName = "All Items Added")
};

USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_BODY()

	FItemAddResult() :
	ActualAmountAdded(0),
	OperationResult(EItemAddResult::IAR_NoItemAdded),
	ResultMessage(FText::GetEmpty())
	{};

	UPROPERTY(BlueprintReadOnly)
	int32 ActualAmountAdded;
	
	UPROPERTY(BlueprintReadOnly)
	EItemAddResult OperationResult;
	
	UPROPERTY(BlueprintReadOnly)
	FText ResultMessage;

	static FItemAddResult AddedNone(const FText& ErrorText)
	{
		FItemAddResult AddedNoneResult;
		AddedNoneResult.ActualAmountAdded = 0;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_NoItemAdded;
		AddedNoneResult.ResultMessage = ErrorText;
		return AddedNoneResult;
	};
	static FItemAddResult AddedPartial(const int32 PartialAmountAdded, const FText& ErrorText)
	{
		FItemAddResult AddedPartialResult;
		AddedPartialResult.ActualAmountAdded = PartialAmountAdded;
		AddedPartialResult.OperationResult = EItemAddResult::IAR_PartialAmountAdded;
		AddedPartialResult.ResultMessage = ErrorText;
		return AddedPartialResult;
	};
	static FItemAddResult AllItemsAdded(const int32 AmountAdded, const FText& MessageText)
	{
		FItemAddResult AddedAllResult;
		AddedAllResult.ActualAmountAdded = AmountAdded;
		AddedAllResult.OperationResult = EItemAddResult::IAR_AllItemsAdded;
		AddedAllResult.ResultMessage = MessageText;
		return AddedAllResult;
	};
};
/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPV1_API UPlayerInventoryComponent : public UBaseInventoryComponent
{
	GENERATED_BODY()

public:
	/*Variables*/

	//Delegate for updating the inventory 
	FOnInventoryUpdated OnInventoryUpdated;

	//TMap for equipped items and their respective slots 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap<EItemSlots, USPItem*> EquippedItems;
	
	/*Functions*/

	UFUNCTION(Category = "Inventory")
	FItemAddResult HandleAddItem(USPItem* NewItem);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	USPItem* FindMatchingItem(USPItem* ItemIn) const;
	
	UFUNCTION(Category = "Inventory")
	USPItem* FindNextItemByID(USPItem* ItemIn) const;
	
	UFUNCTION(Category = "Inventory")
	USPItem* FindNextPartialStack(USPItem* ItemIn) const;
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveSingleInstanceOfItem(USPItem* ItemToRemove);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 RemoveAmountOfItem(USPItem* ItemIn, int32 AmountToRemove);
	
	UFUNCTION(Category = "Inventory")
	void SplitExistingStack(USPItem* ItemIn, const int32 AmountToSplit);
	
	//Function for equipping items
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void EquipItem(USPItem* ItemToEquip, EItemSlots SlotToEquip);
	
	//Function for un-equipping items
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UnEquipItem(USPItem* ItemToUnEquip, EItemSlots SlotToUnEquip);

	//getter functions
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FORCEINLINE float GetInventoryTotalWeight() const { return InventoryTotalWeight; };
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FORCEINLINE float GetWeightCapacity() const { return InventoryWeightCapacity; };
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FORCEINLINE int32 GetSlotsCapacity() const { return InventorySlotsCapacity; };
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FORCEINLINE TArray<USPItem*> GetInventoryContents() const {return InventoryContents; };

	//setter functions
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FORCEINLINE void SetSlotsCapacity(const int32 NewSlotsCapacity) { InventorySlotsCapacity = NewSlotsCapacity; };
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FORCEINLINE void SetWeightCapacity(const float NewWeightCapacity) {InventoryWeightCapacity = NewWeightCapacity; };

	//Constructor
	UPlayerInventoryComponent();

	/*Overrides*/

protected:
	/*variables*/

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	float InventoryTotalWeight = 0.0f;
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 InventorySlotsCapacity = 50;
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	float InventoryWeightCapacity = 100.0f;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<USPItem>> InventoryContents;
	
	//TMap storing ammo name and amount
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap<EAmmoName, float> Ammo;

	//TMap of owned Currency and the amount
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Currency")
	TMap<ECurrencyName, float> Wallet;
	
	/*functions*/
	FItemAddResult HandleNonStackableItems(USPItem* ItemIn, int32 AmountToAdd);
	int32 HandleStackableItems(USPItem* ItemIn, int32 AmountToAdd);
	int32 CalculateAddedWeightAmount(const USPItem* ItemIn, int32 AmountToAdd) const;
	int32 CalculateNumberForFullStack(const USPItem* StackableItem, int32 InitialRequestedAmount) const;

	void AddNewItem(USPItem* NewItem, const int32 AmountToAdd);
	/*overrides*/
};
