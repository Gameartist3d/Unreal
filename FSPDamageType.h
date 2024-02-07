#pragma once

#include "CoreMinimal.h"
#include "ESPDamageType.h"
#include "FSPDamageType.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct SP_API FSPDamageType
{
	GENERATED_BODY()

public:
	FSPDamageType();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	class UTexture2D* DamageTypeIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	ESPDamageType DamageCategory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageAmount;

	~FSPDamageType();
};
