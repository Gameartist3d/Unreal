#pragma once

#include "CoreMinimal.h"
#include "FSPStaminaStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSPStaminaStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float CurStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float DamStamina;
};
