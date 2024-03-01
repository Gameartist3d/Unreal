// Fill out your copyright notice in the Description page of Project Settings.

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
		StarFire
	};

	enum class EWeaponName : uint8
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
	};

	public:
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
		FWeaponType WeaponType;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TArray<FSPDamageType> WeaponDamageTypes;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		TArray<UWeaponAbility*> WeaponAbilities;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		EWeaponName WeaponName;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
		EWeaponMaterial WeaponMaterial;

		FWeaponStats();


	
	~FWeaponStats();
};
