//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "ESPEquipmentSlot.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESPEquipmentSlot : uint8
{
	LeftHand,
	RightHand,
	Throwable,
	Armor,
	Shield,
	Pet
};
