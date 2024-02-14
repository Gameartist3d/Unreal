// 3DNomad LLC

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

	//Maximum Stamina
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina;

	//Current amount of stamina
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float CurStamina;

	//Damaged stamina, ie. unable to regenerate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float DamStamina;

	//Amount of Stamina to recover
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float RecStamina;
};
