//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "ESPDisciplineNames.h"
#include "EAttributeName.h"
#include "FDiscipline.generated.h"

//Struct for creating Disciplines for Stats component
	
	USTRUCT(BlueprintType)
	struct FDiscipline
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discipline")
	ESPDisciplineNames DisciplineName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Discipline")
	class UTexture2D* DisciplineIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discipline")
	int32 DisciplineLvl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discipline")
	float DisciplineExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Discipline")
	EAttributeName ParentAttribute;
	
	FDiscipline()
		:
		DisciplineName(ESPDisciplineNames::Strength),
		DisciplineIcon(nullptr),
		DisciplineLvl(1),
		DisciplineExp(0.0f),
		ParentAttribute(EAttributeName::Physical)
		{
		}
	FDiscipline(ESPDisciplineNames name, UTexture2D* icon, int32 lvl, float exp, EAttributeName parent)
		:
		DisciplineName(name),
		DisciplineIcon(icon),
		DisciplineLvl(lvl),
		DisciplineExp(exp),
		ParentAttribute(parent)
		{
		}
};
