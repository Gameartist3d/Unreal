#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "FWeaponStats.h"
#include "WeaponItem.generated.h"

/**
 * 
 */

UCLASS(Abstract, BlueprintType, Blueprintable, EditInLineNew, DefaultToInstanced)
class SP_API UWeaponItem : public UBaseItem
{
	GENERATED_BODY()

public:

	UWeaponItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FWeaponStats WeaponStats;


protected:

	virtual void Use(class ASPCharacter* Character)override;
	
};
