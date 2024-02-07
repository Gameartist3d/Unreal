#pragma once

#include "CoreMinimal.h"
#include "ESPDamageType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ESPDamageType : uint8 {
	Blunt,
	Slice,
	Pierce,
	Shock,
	Poison,
	Fire,
	Ice,
	Sanity,
	Stamina,
	Demonic

};
