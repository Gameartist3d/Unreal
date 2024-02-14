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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	ESPDisciplineNames ParentDiscipline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	ESPDisciplineNames MinorDiscipline;

};
