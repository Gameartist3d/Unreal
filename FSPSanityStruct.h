//3DNomad LLC

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
	float CurSanity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
	float DamSanity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
	float RecSanity;
};
