//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "SPBaseItem.h"
#include "ESPDamageType.h"
#include "ShieldItem.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EShieldColour : uint8
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

UCLASS(Abstract, BlueprintType, Blueprintable, DefaultToInstanced)
class SP_API AShieldItem : public ASPBaseItem
{
	GENERATED_BODY()

public:

	AShieldItem();

	//Shield Strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float ShieldStrength;

	//Shield Current Strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float ShieldCurrentStrength;

	//Shield Regen Rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float ShieldRegenRate;

	//float for shield hacked amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float ShieldHackedAmount;

	//Shield Regen Delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float ShieldRegenDelay;

	//Shield Resistances
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances")
	TMap<ESPDamageType, float> ShieldResistances;

	//Shield Colour
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	EShieldColour ShieldColour;

	//bool to check if shield has broken
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool bShieldBroken = false;
	
	//Function to update bshieldbroken if shield is broken
	UFUNCTION(BlueprintCallable, Category = "Shield")
	void UpdateShieldBroken();


protected:

	virtual void Use(class ASPCharacter* Character)override;
	
};
