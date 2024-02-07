#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "StatsComponent.h"
#include "HealthItem.generated.h"


/**
 * 
 */
UCLASS()
class UHealthItem : public UBaseItem
{
	GENERATED_BODY()

public:

	UHealthItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float HealthtoRecover;

	
protected: 

	virtual void Use(class ASPCharacter* Character)override;
	
};
