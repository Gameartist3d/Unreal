//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "FAttribute.h"
#include "FDiscipline.h"
#include "FSkill.h"
#include "BaseStatsComponent.h"
#include "DefaultCharacter.h"
#include "Spell.h"
#include "PlayerStatsComponent.generated.h"

/**
 * 
 */

//Delegates for updating Player Attributes
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillUpdated, ESkillName, Skillname);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisciplineUpdated, EDisciplineName, Disciplinename);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeUpdated, EAttributeName, Attributename);

UCLASS()
class SPV1_API UPlayerStatsComponent : public UBaseStatsComponent
{
	GENERATED_BODY()

public:
	/*Variables*/

	//Delegate for skill update
	UPROPERTY(BlueprintAssignable, Category = "Skills")
	FOnSkillUpdated OnSkillUpdated;

	//Delegate for discipline update
	UPROPERTY(BlueprintAssignable, Category = "Disciplines")
	FOnDisciplineUpdated OnDisciplineUpdated;

	//Delegate for attribute update
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnAttributeUpdated OnAttributeUpdated;

	//Variable to store the owner
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Owner")
	ADefaultCharacter* OwnerCharacter;

	//TArray containing all the attributes
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Stats")
	TArray<FAttribute> Attributes;

	//TArray containing all the disciplines
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Stats")
	TArray<FDiscipline> Disciplines;

	//TArray containing all the skills
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Stats")
	TArray<FSkill> Skills;

	//Tarray of known spells
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Stats")
	TArray<USpell*> Spells;
	

	/*Functions*/

	UPlayerStatsComponent();
	
	//Function to add exp to skill
	UFUNCTION(BlueprintCallable, Category = "Skills")
	void AddSkillExp(ESkillName Skillname, float ExptoAdd);

	//Function to check if skill lvl has increased
	UFUNCTION(BlueprintCallable, Category = "Skills")
	void CheckSkilllvlUp(FSkill& Skill);

	//function to return int32 lvl of skill
	UFUNCTION(BlueprintCallable, Category = "Get Stats")
	int32 GetSkilllvl(ESkillName Skillname);

	//Getter for the Skills TArray
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE TArray<FSkill> GetSkills() const {return Skills;};

	//Function to add exp to attribute
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void AddAttributeExp(EAttributeName attributename, float ExptoAdd);

	//Function to check if attribute lvl has increased
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void CheckAttributelvlUp(FAttribute& attribute);

	//function to return int32 lvl of attribute
	UFUNCTION(BlueprintCallable, Category = "Get Stats")
	int32 GetAttributelvl(EAttributeName Attributename);

	//Getter for the Attributes TArray
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE TArray<FAttribute> GetSPAttributes() const {return Attributes;};

	//Function to add exp to discipline
	UFUNCTION(BlueprintCallable, Category = "Disciplines")
	void AddDisciplineExp(EDisciplineName DisciplineName, float ExpToAdd);

	//Function to check if discipline lvl has increased
	UFUNCTION(BlueprintCallable, Category = "Disciplines")
	void CheckDisciplinelvlUp(FDiscipline& Discipline);

	//function to return int32 lvl of discipline
	UFUNCTION(BlueprintCallable, Category = "Get Stats")
	int32 GetDisciplinelvl(EDisciplineName DisciplineName);

	//Getter for the Discipline Tarray
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE TArray<FDiscipline> GetDisciplines() const {return Disciplines;};

	/*Overrides*/

protected:
	/*variables*/

private:
	/*Variables*/
	/*Functions*/

	//Functions to search stats objects by their enumerator name
	FAttribute* FindAttributeByName(EAttributeName Attributename);
	FDiscipline* FindDisciplineByName(EDisciplineName Disciplinename);
	FSkill* FindSkillByName(ESkillName Skillname);
};
