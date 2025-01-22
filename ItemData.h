//3DNomad LLC
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemData.generated.h"

/**
 * 
 */


 //Enum for the different categories of Items
UENUM(BlueprintType)
enum class EItemCategory : uint8
{
	Weapon UMETA(DisplayName = "Weapon"),
	Armor UMETA(DisplayName = "Armor"),
	Shield UMETA(DisplayName = "Shield"),
	Consumable UMETA(DisplayName = "Consumable"),
	Tool UMETA(DisplayName = "Tool"),
	Mission UMETA(DisplayName = "Mission"),
	Material UMETA(DisplayName = "Material"),
	Ammo UMETA(DisplayName = "Ammo"),
	Throwable UMETA(DisplayName = "Throwable"),
	Currency UMETA(DisplayName = "Currency"),
	Misc UMETA(DisplayName = "Miscellaneous")
};

//Enum for the different categories of Items
UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary"),
	Mythic UMETA(DisplayName = "Mythic"),
	Unique UMETA(DisplayName = "Unique")
};

//Enum for the different equipment slots available 
UENUM(BlueprintType)
enum class EItemSlots : uint8
{
	MainHand UMETA(DisplayName = "MainHand"),
	OffHand UMETA(DisplayName = "OffHand"),
	Throwable UMETA(DisplayName = "Throwable"),
	Armor UMETA(DisplayName = "Armor"),
	Shield UMETA(DisplayName = "Shield"),
	Pet UMETA(DisplayName = "ERB")
};

USTRUCT()
struct FItemTextData
{
	GENERATED_BODY()
	
	//Item Name
	UPROPERTY(EditAnywhere, Category = "TextData")
	FText ItemName;

	//Item Description
	UPROPERTY(EditAnywhere, Category = "TextData")
	FText ItemDescription;

	UPROPERTY(EditAnywhere, Category = "TextData")
	EInteractionName InteractionName;
};

USTRUCT()
struct FItemNumericData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "NumericData")
	bool bStackable;

	UPROPERTY(EditAnywhere, Category = "NumericData")
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, Category = "NumericData")
	float Weight;

	//Float value of the item
	UPROPERTY(EditAnywhere, Category = "NumericData")
	float ItemValue;

};

USTRUCT()
struct FItemAssetData 
{
	GENERATED_BODY()

	//Item Icon
	UPROPERTY(EditAnywhere, Category = "AssetData")
	TObjectPtr<UTexture2D> ItemIcon;

	//StaticMesh Asset for the item
	UPROPERTY(EditAnywhere, Category = "AssetData")
	TObjectPtr<UStaticMesh> ItemStaticMesh;

	//StaticMesh Asset for the item
	UPROPERTY(EditAnywhere, Category = "AssetData")
	TObjectPtr<USkeletalMesh> ItemSkeletalMesh;

	//Pickup Sound effect
	UPROPERTY(EditAnywhere, Category = "AssetData")
	TObjectPtr<USoundBase> PickupSound;

};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FName ID;
	
	UPROPERTY(EditAnywhere, Category = "ItemData")
	EItemCategory ItemCategory;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	EItemRarity ItemRarity;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	TArray<EItemSlots> ItemSlots;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemNumericData ItemNumericData;

	UPROPERTY(EditAnywhere, Category = "ItemData")
	FItemAssetData ItemAssetData;
	
};

