#pragma once

#include "CoreMinimal.h"
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
};
