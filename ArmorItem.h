//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "SPBaseItem.h"
#include "ESPHealthVarNames.h"
#include "ESPDamageType.h"
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

UCLASS(BlueprintType, Blueprintable, DefaultToInstanced)
class SP_API AArmorItem : public ASPBaseItem
{
	GENERATED_BODY()

public:

	AArmorItem();

	//Damage Resistance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances")
	TMap<ESPDamageType, float> ArmorResistances;

	//Health variable names that will be affected by the armor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	TArray<ESPHealthVarNames> AffectedHealthVariables;

	//Armor Colour
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Colour")
	EArmorColour Colour;

protected:

	virtual void Use(class ASPCharacter* Character)override;
	
};
