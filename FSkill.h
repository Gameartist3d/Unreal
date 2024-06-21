 // 3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "ESPSkillNames.h"
#include "ESPDisciplineNames.h"
#include "FSkill.generated.h"

//Struct for Skill Variables

USTRUCT(BlueprintType)
struct SP_API FSkill
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	ESPSkillNames SkillName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
	class UTexture2D* SkillIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	int32 SkillLvl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	float SkillExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Disciplines")
	ESPDisciplineNames ParentDiscipline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Disciplines")
	ESPDisciplineNames MinorDiscipline;

	FSkill()
		: SkillName(ESPSkillNames::MartialCombat),
		SkillIcon(nullptr),
		SkillLvl(1),
		SkillExp(0.0f),
		ParentDiscipline(ESPDisciplineNames::Strength),
		MinorDiscipline(ESPDisciplineNames::Endurance)
	{
	}
	FSkill(ESPSkillNames name, UTexture2D* icon, int32 lvl, float exp, ESPDisciplineNames parent, ESPDisciplineNames minor)
		: SkillName(name),
		SkillIcon(icon),
		SkillLvl(lvl),
		SkillExp(exp),
		ParentDiscipline(parent),
		MinorDiscipline(minor)
	{
	}
};
