//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "ESPHealthVarNames.h"
#include "FHealthVariables.generated.h"


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

    //health to recover
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float RecHealth;

    //health that is poisoned
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float PoisHealth;

	FHealthVariables();
	~FHealthVariables();
};
