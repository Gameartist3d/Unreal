#pragma once

#include "CoreMinimal.h"
#include "ESPCurrency.h"
#include "FCurrency.generated.h"

/**Struct for creating new Currency types
 */
USTRUCT(BlueprintType)
struct FCurrency
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency")
	ESPCurrency CurrencyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency")
	class UTexture2D* CurrencyIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency")
	float TotalInWallet = 0.0f;

};
