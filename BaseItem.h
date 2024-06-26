//3DNomad LLC
/*DEPRECATED!!!!!!*/
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FCurrency.h"
#include "ESPItemType.h"
#include "ESPItemRarity.h"
#include "ESPEquipmentSlot.h"
#include "BaseItem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInLineNew, DefaultToInstanced)
class SP_API UBaseItem : public UObject
{
	GENERATED_BODY()

public:

	UBaseItem();

	virtual class UWorld* GetWorld() const { return World; };

	UPROPERTY(Transient)
	class UWorld* World;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText UseActionText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UStaticMesh* PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	class UTexture2D* ItemThumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	ESPItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	ESPItemRarity ItemRarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<ESPEquipmentSlot> ItemSlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float ItemWeight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0f))
	TArray<FCurrency> ItemValue;

	UPROPERTY()
	class UInventoryComponent* OwnerInventory;

	virtual void Use(class ASPCharacter* Character) PURE_VIRTUAL(UBaseItem, );

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class ASPCharacter* Character);
};
