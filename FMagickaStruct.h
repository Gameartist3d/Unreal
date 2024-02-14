// 3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "FMagickaStruct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMagickaStruct
{
	GENERATED_BODY()

	//Max amount of magicka 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float MaxMagic;

	//Current amount of magicka
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float CurMagic;

	//Amount of Magicka that has slowed regeneration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float MagicFatigue;

	//Speed for channeling spells
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float ChannelSpeed;

	//Number of spells character is able to queue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	int32 SpellStackAmount;

	//Damaged Magicka
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float DamMagic;

	//Magic to Recover
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float RecMagic;

	FMagickaStruct();
};
