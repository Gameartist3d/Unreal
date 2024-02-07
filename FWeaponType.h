#pragma once

#include "CoreMinimal.h"
#include "FWeaponType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class FWeaponType{
	Martial,
	OneHandMartial,
	TwoHandMartial,
	OneHandProjectile,
	TwoHandProjectile
};
