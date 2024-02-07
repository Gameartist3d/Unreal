#pragma once

#include "CoreMinimal.h"
#include "FWeaponType.h"
#include "FSPDamageType.h"
#include "WeaponAbility.h"
#include "FWeaponStats.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()

	public:
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FWeaponType WeaponType;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TArray<FSPDamageType> WeaponDamageTypes;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TArray<UWeaponAbility*> WeaponAbilities;

		FWeaponStats();


	
	~FWeaponStats();
};
