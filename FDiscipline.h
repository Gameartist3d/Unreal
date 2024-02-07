#pragma once

#include "CoreMinimal.h"
#include "ESPDisciplineNames.h"
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


	
};
