//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "EPrivacyLevel.generated.h"

UENUM(BlueprintType)
enum class EPrivacyLevel : uint8
{
	Private UMETA(DisplayName = "Private"),
	Public UMETA(DisplayName = "Public"),
	Protected UMETA(DisplayName = "Protected")
};
