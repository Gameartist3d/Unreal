//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "ESPHealthVarNames.h"
#include "ESPDamageType.h"
#include "EDamageLevel.h"
#include "FHealthVariables.generated.h"


UENUM(BlueprintType)
enum class EHeatLevel : uint8
{
    Normal,
    Warm,
    Hot,
    Burning
};

UENUM(BlueprintType)
enum class EColdLevel : uint8
{
	Normal,
	Cool,
	Freezing,
	Frozen
};

UENUM(BlueprintType)
enum class EBleedLevel : uint8
{
	None,
	Light,
	Medium,
	Heavy
};

UENUM(BlueprintType)
enum class ECrushLevel : uint8
{
	None,
	Bruised,
	Strained,
	Broken
};

UENUM(BlueprintType)
enum class EShockLevel : uint8
{
	None,
	Light,
    Spasms,
    Seizure
};

UENUM(BlueprintType)
enum class EPoisonLevel : uint8
{
	None,
	Light,
    Infected,
    Toxic
};

UENUM(BlueprintType)
enum class EDemonicCorruptionLevel : uint8
{
	None,
	Light,
	Conflicted,
	Corrupted
};

USTRUCT(BlueprintType)
struct FHealthVariables
{
    GENERATED_BODY()

    //Health variable name
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    ESPHealthVarNames HealthVariableName;

    //Icon used for UI
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
    class UTexture2D* HVariableIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
    bool isLeftAppendage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
    bool isRightAppendage;

    //maximum health
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float MaxHealth;

    //current health amount
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float CurHealth;

    //damaged health
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float DamHealth;

    //Enum for heat level
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherCondition")
    EHeatLevel HeatLevel;

    //Heat amount of the body part
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherCondition")
    float HeatAmount;

    //Enum for cold level
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherCondition")
    EColdLevel ColdLevel;

    //Cold amount of the body part
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "WeatherCondition")
    float ColdAmount;

    //health to recover
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float RecHealth;

    //Enum for bleed level
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    EBleedLevel BleedLevel;

    //Amount the body part is bleeding
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float BleedAmount;

    //Enum for crush level
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    ECrushLevel CrushLevel;

    //Amount the body part is crushed
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float CrushAmount;

    //Enum for shock level
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    EShockLevel ShockLevel;

    //Amount the body part is shocked
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float ShockAmount;

    //Enum for poison level
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    EPoisonLevel PoisonLevel;

    //health that is poisoned
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float PoisHealth;

    //Enum for demonic corruption level
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    EDemonicCorruptionLevel DemonicCorruptionLevel;

    //Amount of demonic corruption
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float DemonicCorruption;

    //Damage Level
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    EDamageLevel DamageLevel;

    //Damage Resistance
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resistances")
    TMap<ESPDamageType, float> Resistances;

    //TArray of Strings of bone names associated with this health variable
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    TArray<FString> BoneNames;

    FHealthVariables()
        :HealthVariableName(ESPHealthVarNames::AssCheek),
        HVariableIcon(nullptr),
        isLeftAppendage(false),
        isRightAppendage(false),
        MaxHealth(100.0f),
        CurHealth(100.0f),
        DamHealth(0.0f),
        HeatLevel(EHeatLevel::Normal),
        HeatAmount(0.0f),
        ColdLevel(EColdLevel::Normal),
        ColdAmount(0.0f),
        RecHealth(0.0f),
        BleedLevel(EBleedLevel::None),
        BleedAmount(0.0f),
        CrushLevel(ECrushLevel::None),
        CrushAmount(0.0f),
        ShockLevel(EShockLevel::None),
        ShockAmount(0.0f),
        PoisonLevel(EPoisonLevel::None),
        PoisHealth(0.0f),
        DemonicCorruptionLevel(EDemonicCorruptionLevel::None),
        DemonicCorruption(0.0f),
        DamageLevel(EDamageLevel::None),
        Resistances({}),
        BoneNames()
        
    {
    }
    FHealthVariables(ESPHealthVarNames name, UTexture2D* icon, bool isleft, bool isright, float maxhealth, float curhealth, float damhealth, EHeatLevel heatlevel, float heatamount, EColdLevel coldlevel, float coldamount, float rechealth, EBleedLevel bleedlevel, float bleedamount, ECrushLevel crushlevel, float crushamount, EShockLevel shocklevel, float shockamount, EPoisonLevel poisonlevel, float poishealth, EDemonicCorruptionLevel demoniccorruptionlevel, float demoniccorruption, EDamageLevel damagelevel, TMap<ESPDamageType, float> resistances, TArray<FString> bonenames)
        :HealthVariableName(name),
        HVariableIcon(icon),
        isLeftAppendage(isleft),
        isRightAppendage(isright),
        MaxHealth(maxhealth),
        CurHealth(curhealth),
        DamHealth(damhealth),
        HeatLevel(heatlevel),
        HeatAmount(heatamount),
        ColdLevel(coldlevel),
        ColdAmount(coldamount),
        RecHealth(rechealth),
        BleedLevel(bleedlevel),
        BleedAmount(bleedamount),
        CrushLevel(crushlevel),
        CrushAmount(crushamount),
        ShockLevel(shocklevel),
        ShockAmount(shockamount),
		PoisonLevel(poisonlevel),
		PoisHealth(poishealth),
		DemonicCorruptionLevel(demoniccorruptionlevel),
		DemonicCorruption(demoniccorruption),
		DamageLevel(damagelevel),
		Resistances(resistances),
		BoneNames(bonenames)

    {
    }
	~FHealthVariables();
};
