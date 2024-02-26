//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "ESPItemRarity.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESPItemRarity : uint8
{
	Common,
	Uncommon,
	Scarse,
	Rare,
	Legendary,
	Unique
};
