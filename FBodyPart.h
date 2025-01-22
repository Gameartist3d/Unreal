//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "FDamage.h"
#include "FBodyPart.generated.h"

/**
 * 
 */

 //Enum for BodyPart names
UENUM(BlueprintType)
enum class EBodyPartName : uint8
{
	Head UMETA(DisplayName = "Head"),
	Torso UMETA(DisplayName = "Torso"),
	LeftArm UMETA(DisplayName = "LeftArm"),
	RightArm UMETA(DisplayName = "RightArm"),
	LeftLeg UMETA(DisplayName = "LeftLeg"),
	RightLeg UMETA(DisplayName = "RightLeg"),
	LeftWing UMETA(DisplayName = "LeftWing"),
	RightWing UMETA(DisplayName = "RightWing"),
	Tail UMETA(DisplayName = "Tail"),
	Eye UMETA(DisplayName = "Eye"),
	Stomach UMETA(DisplayName = "Stomach"),
	AssCheek UMETA(DisplayName = "Asscheek"),
	LeftHand UMETA(DisplayName = "LeftHand"),
	RightHand UMETA(DisplayName = "RightHand"),
	LeftFoot UMETA(DisplayName = "LeftFoot"),
	RightFoot UMETA(DisplayName = "RightFoot"),
	LeftAntenna UMETA(DisplayName = "LeftAtenna"),
	RightAntenna UMETA(DisplayName = "RightAtenna"),
	Tentacle UMETA(DisplayName = "Tentacle"),
	Fin UMETA(DisplayName = "Fin"),
	Beak UMETA(DisplayName = "Beak"),
	Shell UMETA(DisplayName = "Shell"),
	Prop UMETA(DisplayName = "Prop")
};

UENUM(BlueprintType)
enum class EDamageLevel : uint8
{
	None UMETA(DisplayName = "None"),
	Light UMETA(DisplayName = "Light"),
	Medium UMETA(DisplayName = "Medium"),
	Heavy UMETA(DisplayName = "Heavy"),
	Severe UMETA(DisplayName = "Severe"),
	Critical UMETA(DisplayName = "Critical"),
	Destroyed UMETA(DisplayName = "Destroyed")
	
};

UENUM(BlueprintType)
enum class EHeatLevel : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Warm UMETA(DisplayName = "Warm"),
	Hot UMETA(DisplayName = "Hot"),
	Burning UMETA(DisplayName = "Burning")
};

UENUM(BlueprintType)
enum class EColdLevel : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Cool UMETA(DisplayName = "Cool"),
	Freezing UMETA(DisplayName = "Freezing"),
	Frozen UMETA(DisplayName = "Frozen")
};

UENUM(BlueprintType)
enum class EBleedLevel : uint8
{
	None UMETA(DisplayName = "None"),
	Light UMETA(DisplayName = "Light"),
	Medium UMETA(DisplayName = "Medium"),
	Heavy UMETA(DisplayName = "Heavy")
};

UENUM(BlueprintType)
enum class ECrushLevel : uint8
{
	None UMETA(DisplayName = "None"),
	Bruised UMETA(DisplayName = "Bruised"),
	Strained UMETA(DisplayName = "Strained"),
	Broken UMETA(DisplayName = "Broken")
};

UENUM(BlueprintType)
enum class EShockLevel : uint8
{
	None UMETA(DisplayName = "None"),
	Light UMETA(DisplayName = "Light"),
	Spasms UMETA(DisplayName = "Spasms"),
	Seizure UMETA(DisplayName = "Seizure")
};

UENUM(BlueprintType)
enum class EPoisonLevel : uint8
{
	None UMETA(DisplayName = "None"),
	Light UMETA(DisplayName = "Light"),
	Infected UMETA(DisplayName = "Infected"),
	Toxic UMETA(DisplayName = "Toxic")
};

UENUM(BlueprintType)
enum class EDemonicCorruptionLevel : uint8
{
	None UMETA(DisplayName = "None"),
	Light UMETA(DisplayName = "Light"),
	Conflicted UMETA(DisplayName = "Conflicted"),
	Corrupted UMETA(DisplayName = "Corrupted")
};

USTRUCT(BlueprintType)
struct FBodyPart
{
	GENERATED_BODY()

	//Name of the BodyPart
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	EBodyPartName BodyPartName;

	//Icon used for UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
	class UTexture2D* HVariableIcon;

	//Array of Bone Names (From Skeletal Mesh) associated with the BodyPart
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	TArray <FString> BoneNames;

	//Max Health of the BodyPart
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float MaxHealth;

	//Current Health of the BodyPart
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float CurHealth;

	//Damaged Health that will not restore over time
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float DamHealth;

	//Damage Level of the BodyPart
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	EDamageLevel DamageLevel;

	//Recovering Health that is repairing damaged health over time
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float RecHealth;

	//Amount of Poison the BodyPart has taken
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float PoisAmount;

	//Enum for poison level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	EPoisonLevel PoisonLevel;

	//Amount of bleeding, once it crosses CurHealth, Hp will drop by the ratio
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float BleedAmount;

	//Enum for bleed level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	EBleedLevel BleedLevel;

	//Amount of Burning the BodyPart has taken
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float BurnAmount;

	//Enum for heat level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherCondition")
	EHeatLevel HeatLevel;

	//Amount of Freezing the BodyPart has taken
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float FreezeAmount;

	//Enum for cold level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherCondition")
	EColdLevel ColdLevel;

	//Amount of Shock the BodyPart has taken
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float ShockAmount;

	//Enum for shock level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	EShockLevel ShockLevel;

	//How crushed the BodyPart is, if CrushAmount is greater than MaxHealth, the bodypart will break
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float CrushAmount;

	//Enum for crush level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	ECrushLevel CrushLevel;

	//How cursed the BodyPart is, the curse will manifest as it reaches MaxHealth
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float CursedAmount;

	//Enum for demonic corruption level
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
	EDemonicCorruptionLevel DemonicCorruptionLevel;

	//Speed this bodypart can recover from damage
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Attribute")
	float RecSpeed;

	//TArray of DamageType resistances
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Stats")
	TMap <EDamageType, float> Resistances;

	FBodyPart()
		: BodyPartName(EBodyPartName::AssCheek),
		HVariableIcon(nullptr),
		BoneNames(),
		MaxHealth(0.0f),
		CurHealth(0.0f),
		DamHealth(0.0f),
		DamageLevel(EDamageLevel::None),
		RecHealth(0.0f),
		PoisAmount(0.0f),
		PoisonLevel(EPoisonLevel::None),
		BleedAmount(0.0f),
		BleedLevel(EBleedLevel::None),
		BurnAmount(0.0f),
		HeatLevel(EHeatLevel::Normal),
		FreezeAmount(0.0f),
		ColdLevel(EColdLevel::Normal),
		ShockAmount(0.0f),
		ShockLevel(EShockLevel::None),
		CrushAmount(0.0f),
		CrushLevel(ECrushLevel::None),
		CursedAmount(0.0f),
		DemonicCorruptionLevel(EDemonicCorruptionLevel::None),
		RecSpeed(0.0f),
		Resistances()
	{
	}
	FBodyPart(EBodyPartName inname, UTexture2D* inicon, TArray <FString> inbonenames, float inmaxhealth, float incurhealth, float indamhealth, EDamageLevel indamlvl, float inrechealth, float inpoishealth, EPoisonLevel inpoislvl, float inbleedamount, EBleedLevel inbleedlvl, float inburnamount, EHeatLevel inheatlvl, float infrzamount, EColdLevel incoldlvl, float inshockamount, EShockLevel inshocklvl, float incrushamount, ECrushLevel incrushlvl, float incurseamount, EDemonicCorruptionLevel incurselvl, float inrecspeed, TMap <EDamageType, float> inresistances)
		: BodyPartName(inname),
		HVariableIcon(inicon),
		BoneNames(inbonenames),
		MaxHealth(inmaxhealth),
		CurHealth(incurhealth),
		DamHealth(indamhealth),
		DamageLevel(indamlvl),
		RecHealth(inrechealth),
		PoisAmount(inpoishealth),
		PoisonLevel(inpoislvl),
		BleedAmount(inbleedamount),
		BleedLevel(inbleedlvl),
		BurnAmount(inburnamount),
		HeatLevel(inheatlvl),
		FreezeAmount(infrzamount),
		ColdLevel(incoldlvl),
		ShockAmount(inshockamount),
		ShockLevel(inshocklvl),
		CrushAmount(incrushamount),
		CrushLevel(incrushlvl),
		CursedAmount(incurseamount),
		DemonicCorruptionLevel(incurselvl),
		RecSpeed(inrecspeed),
		Resistances(inresistances)
	{
	}
	FBodyPart(const FBodyPart& other)
		: FBodyPart(other.BodyPartName, other.HVariableIcon, other.BoneNames, other.MaxHealth, other.CurHealth, other.DamHealth, other.DamageLevel, other.RecHealth, other.PoisAmount, other.PoisonLevel, other.BleedAmount, other.BleedLevel, other.BurnAmount, other.HeatLevel, other.FreezeAmount, other.ColdLevel, other.ShockAmount, other.ShockLevel, other.CrushAmount, other.CrushLevel, other.CursedAmount, other.DemonicCorruptionLevel, other.RecSpeed, other.Resistances)
	{
	}
	bool operator==(const FBodyPart& other) const
	{
		return Equals(other);
	}

	bool Equals(const FBodyPart& other) const
	{
		return BodyPartName == other.BodyPartName && HVariableIcon == other.HVariableIcon && BoneNames == other.BoneNames && MaxHealth == other.MaxHealth && CurHealth == other.CurHealth && DamHealth == other.DamHealth && DamageLevel == other.DamageLevel && RecHealth == other.RecHealth && PoisAmount == other.PoisAmount && PoisonLevel == other.PoisonLevel && BleedAmount == other.BleedAmount && BleedLevel == other.BleedLevel && BurnAmount == other.BurnAmount && HeatLevel == other.HeatLevel && FreezeAmount == other.FreezeAmount && ColdLevel == other.ColdLevel && ShockAmount == other.ShockAmount && ShockLevel == other.ShockLevel && CrushAmount == other.CrushAmount && CrushLevel == other.CrushLevel && CursedAmount == other.CursedAmount && DemonicCorruptionLevel == other.DemonicCorruptionLevel && RecSpeed == other.RecSpeed && Resistances.GetAllocatedSize() == other.Resistances.GetAllocatedSize();
	}
};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FBodyPart& thing);
#else 
FORCEINLINE uint32 GetTypeHash(const FBodyPart& thing)
{
	uint32 hash = FCrc::MemCrc32(&thing, sizeof(FBodyPart));
	return hash;
}
#endif
