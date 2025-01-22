//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatsWindowWidget.generated.h"

class UPlayerStatsComponent;

/**
 * 
 */
UCLASS()
class SPV1_API UStatsWindowWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	/*variables*/
	UPROPERTY(BlueprintReadOnly, Category="Stats")
	UPlayerStatsComponent* OwnerStatsComponent;

	/*overrides*/
	virtual void NativeOnInitialized() override;
	
};
