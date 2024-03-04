//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "FSPDamageType.h"
#include "FAmmo.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESPAmmoName : uint8
{
	B7G,
	B12G,
	B15G,
	B20G,
	B35G,
	B55G,
	B60G,
	B70G,
	B75G,
	WarpShot2G,
	WarpShot6G,
	HeatSink5G,
	HeatSink10G,
	Rtip10G,
	Rtip15G
};
USTRUCT(BlueprintType)
struct FAmmo
{
	GENERATED_BODY()

	FAmmo();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	ESPAmmoName AmmoName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	TArray<FSPDamageType> AmmoDamageTypes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 AmmoAmount;
};
