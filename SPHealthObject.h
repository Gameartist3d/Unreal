// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SPHealthObject.generated.h"

/**
 * 
 */
UCLASS()
class SP_API USPHealthObject : public UObject
{
	GENERATED_BODY()


public:

	USPHealthObject();

	USTRUCT(BlueprintType)
		struct FSPHealthVariables {
		GENERATED_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		FText HObjectName;

		// Max Health for this body part
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float MaxHealth;

		// Current Health for this body part
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float CurHealth;

		// Current Health that is Damaged
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float DamHealth;

		// Current Health in Recovery Phase
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float RecHealth;

		// Current Health in Poisoned Phase
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		float PoisHealth;
	};
	
};
