//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FDamage.generated.h"

/**
 * 
 */

 //Enum for damagetype
UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Slash UMETA(DisplayName = "Slash"),
	Crush UMETA(DisplayName = "Crush"),
	Pierce UMETA(DisplayName = "Pierce"),
	Burn UMETA(DisplayName = "Burn"),
	Freeze UMETA(DisplayName = "Freeze"),
	Shock UMETA(DisplayName = "Shock"),
	Poison UMETA(DisplayName = "Poison"),
	Bleed UMETA(DisplayName = "Bleed"),
	Sanity UMETA(DisplayName = "Sanity"),
	Stamina UMETA(DisplayName = "Stamina"),
	Magicka UMETA(DisplayName = "Magicka"),
	Demonic UMETA(DisplayName = "Demonic"),
	Divine UMETA(DisplayName = "Divine")
};

USTRUCT(BlueprintType)
struct FDamage
{
	GENERATED_BODY()

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	EDamageType DamageType;
	 
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float DamageValue;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float NegateArmorValue;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float NegateShieldValue;


	FDamage()
		: DamageType(EDamageType::Slash),
		DamageValue(0.0f),
		NegateArmorValue(0.0f),
		NegateShieldValue(0.0f)
	{
	}
	FDamage(EDamageType InDamageType, float InDamageValue, float InNegateArmorValue, float InNegateShieldValue)
		: DamageType(InDamageType),
		DamageValue(InDamageValue),
		NegateArmorValue(InNegateArmorValue),
		NegateShieldValue(InNegateShieldValue)
	{
	}
	FDamage(const FDamage& other)
		: FDamage(other.DamageType, other.DamageValue, other.NegateArmorValue, other.NegateShieldValue)
	{
	}
	bool operator==(const FDamage& other) const
	{
		return Equals(other);
	}

	bool Equals(const FDamage& other) const
	{
		return DamageType == other.DamageType && DamageValue == other.DamageValue && NegateArmorValue == other.NegateArmorValue && NegateShieldValue == other.NegateShieldValue;
	}
};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FDamage& thing);
#else
FORCEINLINE uint32 GetTypeHash(const FDamage& thing)
{
	uint32 hash = FCrc::MemCrc32(&thing, sizeof(FDamage));
	return hash;
}
#endif
