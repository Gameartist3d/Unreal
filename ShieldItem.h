#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ShieldItem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInLineNew, DefaultToInstanced)
class SP_API UShieldItem : public UBaseItem
{
	GENERATED_BODY()

public:

	UShieldItem();



protected:

	virtual void Use(class ASPCharacter* Character)override;
	
};
