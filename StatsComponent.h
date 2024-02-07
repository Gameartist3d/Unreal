#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FHealthVariables.h"
#include "FSPStaminaStruct.h"
#include "FSPSanityStruct.h"
#include "FSPAttribute.h"
#include "FDiscipline.h"
#include "FSkill.h"
#include "FSPDamageType.h"
#include "StatsComponent.generated.h"

//For Updating the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatsUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatsComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 PlayuurLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float PlayuurLvlExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	FSPStaminaStruct Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
	FSPSanityStruct Sanity;

	/**Array of Structs for HealthPoints*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    TArray<FHealthVariables> BodyHealth;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatsUpdated OnStatsUpdated;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void DamageToBodyHealth(FSPDamageType damage, ESPHealthVarNames bodypart);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void AddPlayuurlvlExp(float exptoadd);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void CheckPlayuurlvlup();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void AddAttributeExp(EAttributeName attributename, float ExptoAdd);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void CheckAttributelvlUp(FSPAttribute& attribute);

	UFUNCTION(BlueprintCallable, Category = "Disciplines")
	void AddDisciplineExp(ESPDisciplineNames Disciplinename, float ExptoAdd);

	UFUNCTION(BlueprintCallable, Category = "Disciplines")
	void CheckDisciplinelvlUp(FDiscipline& discipline);

	UFUNCTION(BlueprintCallable, Category = "Skills")
	void AddSkillExp(ESPSkillNames Skillname, float ExptoAdd);

	UFUNCTION(BlueprintCallable, Category = "Skills")
	void CheckSkilllvlUp(FSkill& Skill);




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
	FSPAttribute* FindAttributeByName(EAttributeName Attributename);
	FDiscipline* FindDisciplineByName(ESPDisciplineNames Disciplinename);
	FSkill* FindSkillByName(ESPSkillNames Skillname);
	
};
