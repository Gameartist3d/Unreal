//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "SPItem.h"
#include "FDamage.h"
#include "WeaponItem.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EWeaponMaterial : uint8
{
	Iron,
	Steel,
	Palladium,
	Tungsten,
	Gold,
	Silver,
	Mithril,
	Adamantium,
	Platinum,
	Aluminum,
	Crystal,
	LivingMetal,
	DemonicAmber,
	LightThread,
	TimeGlass,
	Particle,
	Fusion,
	StarFire,
	SaltyTears
};

UENUM(BlueprintType)
enum class EWeaponCategory : uint8
{
	Dagger,
	Knife,
	Blade,
	Sword,
	Rapier,
	Saber,
	Pistol,
	Handgun,
	Revolver,
	Rifle,
	Gun,
	Repeater,
	Railgun,
	Bow,
	Crossbow,
	Launcher,
	Shotgun,
	Lasergun,
	Protongun,
	Spear,
	Lance,
	Boomerang,
	Stave
};

UCLASS(BlueprintType)
class SPV1_API UWeaponItem : public USPItem
{
	GENERATED_BODY()

public:

	
	/*Variables*/
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponCategory WeaponCategory;

	//Tmap of damage types and their values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TMap<EDamageType, float> WeaponDamageTypes;

		//TODO Create Weapon Ability Class
		/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TArray<UWeaponAbility*> WeaponAbilities;*/

	//Weapon Material for further defining the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponMaterial WeaponMaterial = EWeaponMaterial::SaltyTears;

	//float for the aggro this weapon generates
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float AggroAmount = 1.0f;

	//bool to check if weapon is two handed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	bool bIsTwoHanded = false;

	//Physics force applied to the hit actor/object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float PhysicsForce = 1.0f;

	//float amount for the decrease in channeling time the weapon gives per item slot equipped
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float ChannelingDecrease = 0.0f;

	/*Functions*/

	UWeaponItem();

	//Function for comparing damage types againsy health variable resistances, and then applying the residual damage
	UFUNCTION(BlueprintCallable)
	void ApplyDamageTypes(FHitResult HitResult);

	//Function for applying the weapon's physics force to the hit actor bone
	UFUNCTION(BlueprintCallable)
	void ApplyPhysicsForce(FHitResult HitResult);

	/*Overrides*/

	//Override function for copying the item
	//virtual USPItem* CopyItem() override;

private:

	//Function for retrieving the total damage incoming from the weapon
	float CalculateTotalDamage();
};
