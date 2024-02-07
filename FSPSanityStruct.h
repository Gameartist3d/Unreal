#pragma once

#include "CoreMinimal.h"
#include "FSPSanityStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSPSanityStruct
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
	float MaxSanity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float CurSanity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float DamSanity;
};
