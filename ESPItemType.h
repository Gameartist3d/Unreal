//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "ESPItemType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESPItemType : uint8
{
	Weapon,
	Shield,
	Armor,
	Pet,
	Material,
	Consumable,
	Key,
	Actionable,
	Prop,
	Mission,
	Program


};
