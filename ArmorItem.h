//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "SPItem.h"
#include "FDamage.h"
#include "ArmorItem.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EArmorColour : uint8
{
	None,
	White,
	Green,
	Blue,
	Teal,
	Orange,
	Purple,
	Yellow,
	Red,
	Peach,
	Brown,
	Grey,
	LightBlue,
	Pink,
	Rainbow,
	Black
};

UCLASS()
class SPV1_API UArmorItem : public USPItem
{
	GENERATED_BODY()

public:
	/*Variables*/

	//TMap of resistances
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Armor")
		TMap<EDamageType, float> ArmorResistances;

	//Armor Colour
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour")
	EArmorColour Colour;

	/*Functions*/

	UArmorItem();

	/*Overrides*/

	virtual void Use(APlayerCharacter* Character)override;
};
