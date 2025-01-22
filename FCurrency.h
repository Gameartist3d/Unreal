//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FCurrency.generated.h"

/**
 * 
 */

 //Enum for Currency names
UENUM(BlueprintType)
enum class ECurrencyName : uint8
{
	Rupee UMETA(DisplayName = "Rupee"),
	GrotanShekel UMETA(DisplayName = "Grotan Shekel"),
	GalacticShilling UMETA(DisplayName = "Galactic Shilling"),
	Medaos UMETA(DisplayName = "Medaos"),
	Aureus UMETA(DisplayName = "Aureus"),
	SeaShells UMETA(DisplayName = "Sea Shells"),
	Dollas UMETA(DisplayName = "Dollas"),
	Coppers UMETA(DisplayName = "Coppers"),
	BlackSouls UMETA(DisplayName = "Black Souls")
};

USTRUCT(BlueprintType)
struct FCurrency
{
GENERATED_BODY()

UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
ECurrencyName CurrencyName;

UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
UTexture2D* CurrencyIcon;

UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
FText CurrencyDescription;

FCurrency()
	: CurrencyName(ECurrencyName::Medaos),
	CurrencyIcon(nullptr),
	CurrencyDescription(FText::FromString(TEXT("Currency Description")))
{
}
FCurrency(ECurrencyName inname, UTexture2D* inicon, FText indescription)
	: CurrencyName(inname),
	CurrencyIcon(inicon),
	CurrencyDescription(indescription)
{
}
FCurrency(const FCurrency& other)
	: FCurrency(other.CurrencyName, other.CurrencyIcon, other.CurrencyDescription)
{
}
bool operator==(const FCurrency& other) const
{
	return Equals(other);
}

bool Equals(const FCurrency& other) const
{
	return CurrencyName == other.CurrencyName && CurrencyIcon == other.CurrencyIcon && CurrencyDescription.EqualTo(other.CurrencyDescription);
}
};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FCurrency& thing);
#else 
FORCEINLINE uint32 GetTypeHash(const FCurrency& thing)
{
	uint32 hash = FCrc::MemCrc32(&thing, sizeof(FCurrency));
	return hash;
}
#endif

