//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "ESPDamageType.h"
#include "FThrowable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FThrowable
{
	GENERATED_BODY()

	FThrowable();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Throwables")
	FText ThrowableName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Throwables")
	TArray<class FSPDamageType> ThrowableDamageTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Throwables")
	float ThrowablesWeight;

};
