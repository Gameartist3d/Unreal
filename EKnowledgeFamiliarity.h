//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "EKnowledgeFamiliarity.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EKnowledgeFamiliarity : uint8
{

	Unknown UMETA(DisplayName = "Unknown"),

	Familiar UMETA(DisplayName = "Familiar"),

	Unfamiliar UMETA(DisplayName = "Unfamiliar"),

	Wellknown UMETA(DisplayName = "Wellknown")
	
};
