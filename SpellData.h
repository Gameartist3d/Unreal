//3DNomad LLC
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SpellData.generated.h"

/**
 * 
 */
//Enum for the spell names
UENUM(BlueprintType)
enum class ESpellName : uint8
{
	Fireball,
	Lightning,
	Frost,
	Bile,
	Silence,
	Sliver,
	MagicRay,
	SandPryzn
};

USTRUCT(BlueprintType)
struct FSpellTextData
{
	GENERATED_BODY()
	//enumerator name for the spell
	UPROPERTY(EditAnywhere, Category = "TextData")
	ESpellName SpellName;

	//text for the spell description
	UPROPERTY(EditAnywhere, Category = "TextData")
	FText SpellDescription;

	//text for the ui tooltip
	UPROPERTY(EditAnywhere, Category = "TextData")
	FText SpellToolTipText;
	
};

USTRUCT(BlueprintType)
struct FSpellNumericData
{
	GENERATED_BODY()
	//float cost to cast the spell
	UPROPERTY(EditAnywhere, Category = "NumericData")
	float SpellCost;

	//Overall difficulty float value
	UPROPERTY(EditAnywhere, Category = "NumericData")
	float SpellDifficulty;

	//int32 for the level of the spell
	UPROPERTY(EditAnywhere, Category = "NumericData")
	int32 SpellLevel;

	//float for the amount needed to level up the spell
	UPROPERTY(EditAnywhere, Category = "NumericData")
	float SpellExpToLvl;

	//float for the amount of current exp
	UPROPERTY(EditAnywhere, Category = "NumericData")
	float SpellCurExp;
	
};

USTRUCT(BlueprintType)
struct FSpellAssetData
{
	GENERATED_BODY()
	//Icon for the UI widget
	UPROPERTY(EditAnywhere, Category = "AssetData")
	TObjectPtr<UTexture2D> SpellIcon;

	//Icon for the tooltip widget
	UPROPERTY(EditAnywhere, Category = "AssetData")
	TObjectPtr<UTexture2D> SpellToolTipIcon;

	//Pickup Sound effect
	UPROPERTY(EditAnywhere, Category = "AssetData")
	TObjectPtr<USoundBase> CastSound;
	
};

USTRUCT(BlueprintType)
struct FSpellData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "SpellData")
	FSpellTextData SpellTextData;

	UPROPERTY(EditAnywhere, Category = "SpellData")
	FSpellNumericData SpellNumericData;

	UPROPERTY(EditAnywhere, Category = "SpellData")
	FSpellAssetData SpellAssetData;
	
};
