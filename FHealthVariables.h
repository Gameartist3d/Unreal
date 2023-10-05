// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FHealthVariables.generated.h"


USTRUCT(BlueprintType)
struct FHealthVariables
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    FText HealthVariableName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health")
    class UTexture2D* HVariableIcon;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float MaxHealth;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float CurHealth;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float DamHealth;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float RecHealth;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
    float PoisHealth;

	FHealthVariables();
	~FHealthVariables();
};
