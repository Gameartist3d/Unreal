#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ArmorItem.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInLineNew, DefaultToInstanced)
class SP_API UArmorItem : public UBaseItem
{
	GENERATED_BODY()

public:

	UArmorItem();

protected:

	virtual void Use(class ASPCharacter* Character)override;
	
};
