//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "SPBaseItem.h"
#include "FWeaponStats.h"
#include "FSkill.h"
#include "WeaponItem.generated.h"

/**
 * 
 */

UCLASS(BlueprintType, Blueprintable, DefaultToInstanced)
class SP_API AWeaponItem: public ASPBaseItem
{
	GENERATED_BODY()

	float CalculateTotalDamage();

public:

	AWeaponItem();

	//Weapon Stats Struct
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FWeaponStats WeaponStats;

	//Weapon Skill Bonuses
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	TMap<ESPSkillNames, float> SkillBonuses;

	//Weapon Aggro Amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float AggroAmount;

	//bool to check if weapon is two handed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool bIsTwoHanded;

	//Physics force applied to the hit actor/object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float PhysicsForce;

	//Skeletal Mesh for the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMesh* WeaponMesh;

	//Function for comparing damage types againsy health variable resistances, and then applying the residual damage
	UFUNCTION(BlueprintCallable)
	void ApplyDamageTypes(FHitResult hitresult);

	//Function for applying the weapon's physics force to the hit actor bone
	UFUNCTION(BlueprintCallable)
	void ApplyPhysicsForce(FHitResult hitresult, ASPCharacter* Character);
	



protected:

	virtual void Use(class ASPCharacter* Character)override;
	
};
