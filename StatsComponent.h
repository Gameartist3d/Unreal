// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FHealthVariables.h"
#include "FSPStaminaStruct.h"
#include "FSPSanityStruct.h"
#include "FMagickaStruct.h"
#include "FSPAttribute.h"
#include "FDiscipline.h"
#include "FSkill.h"
#include "FSPDamageType.h"
#include "StatsComponent.generated.h"

//For Updating the UI, Related Functions
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatsUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSanityUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMagickaUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBodyHealthUpdated, ESPHealthVarNames, BodyPart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillUpdated, ESPSkillNames, Skillname);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisciplineUpdated, ESPDisciplineNames, Disciplinename);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeUpdated, EAttributeName, Attributename);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

	//playuur's level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 PlayuurLevel;

	//current playuur level experience
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float PlayuurLvlExp;

	//Struct holding Stamina variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	FSPStaminaStruct Stamina;

	//Struct holding Sanity Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
	FSPSanityStruct Sanity;

	//Struct holding magicka variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
	FMagickaStruct Magicka;

	/**Array of Structs for HealthPoints*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    TArray<FHealthVariables> BodyHealth;

	//Delegate for stats update
	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatsUpdated OnStatsUpdated;

	//Delegate for Stamina stats update
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnStaminaUpdated OnStaminaUpdated;

	//Delegate for sanity stats update
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnSanityUpdated OnSanityUpdated;

	//Delegate for magicka stats update
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnMagickaUpdated OnMagickaUpdated;

	//Delegate for bodyhealth update
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnBodyHealthUpdated OnBodyHealthUpdated;

	//Delegate for attribute update
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeUpdated OnAttributeUpdated;

	//Delegate for discipline update
	UPROPERTY(BlueprintAssignable, Category = "Disciplines")
	FOnDisciplineUpdated OnDisciplineUpdated;

	//Delegate for skill update
	UPROPERTY(BlueprintAssignable, Category = "Skills")
	FOnSkillUpdated OnSkillUpdated;

	//add damage type to specific bodypart
	UFUNCTION(BlueprintCallable, Category = "Health")
	void DamageToBodyHealth(FSPDamageType damage, ESPHealthVarNames bodypart);

	//Function to add exp to Playuurlvlexp
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void AddPlayuurlvlExp(float exptoadd);

	//Function to check if playuur lvl has increased
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void CheckPlayuurlvlup();

	//Function to add exp to attribute
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void AddAttributeExp(EAttributeName attributename, float ExptoAdd);

	//Function to check if attribute lvl has increased
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void CheckAttributelvlUp(FSPAttribute& attribute);

	//Function to add exp to discipline
	UFUNCTION(BlueprintCallable, Category = "Disciplines")
	void AddDisciplineExp(ESPDisciplineNames Disciplinename, float ExptoAdd);

	//Function to check if discipline lvl has increased
	UFUNCTION(BlueprintCallable, Category = "Disciplines")
	void CheckDisciplinelvlUp(FDiscipline& discipline);

	//Function to add exp to skill
	UFUNCTION(BlueprintCallable, Category = "Skills")
	void AddSkillExp(ESPSkillNames Skillname, float ExptoAdd);

	//Function to check if skill lvl has increased
	UFUNCTION(BlueprintCallable, Category = "Skills")
	void CheckSkilllvlUp(FSkill& Skill);

	//function to return int32 lvl of skill
	UFUNCTION(BlueprintCallable, Category = "Get Stats")
	int32 GetSkilllvl(ESPSkillNames Skillname);

	//function to return int32 lvl of discipline
	UFUNCTION(BlueprintCallable, Category = "Get Stats")
	int32 GetDisciplinelvl(ESPDisciplineNames Disciplinename);

	//function to return int32 lvl of attribute
	UFUNCTION(BlueprintCallable, Category = "Get Stats")
	int32 GetAttributelvl(EAttributeName Attributename);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/**Array of Attributes*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	TArray<FSPAttribute> Attributes;

	/**Array of Disciplines*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	TArray<FDiscipline> Disciplines;

	/**Array of Skills*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	TArray<FSkill> Skills;

private:
	//Functions to search stats objects by their enumerator name
	FSPAttribute* FindAttributeByName(EAttributeName Attributename);
	FDiscipline* FindDisciplineByName(ESPDisciplineNames Disciplinename);
	FSkill* FindSkillByName(ESPSkillNames Skillname);
	
};
