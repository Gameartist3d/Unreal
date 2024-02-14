//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "FSPDamageType.h"
#include "FAmmo.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FAmmo
{
	GENERATED_BODY()


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	FText AmmoName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	TArray<FSPDamageType> AmmoDamageTypes;
};
