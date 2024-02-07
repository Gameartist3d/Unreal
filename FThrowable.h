#pragma once

#include "CoreMinimal.h"
#include "FThrowable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FThrowable
{
	GENERATED_BODY()


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Throwables")
	FText ThrowableName;

};
