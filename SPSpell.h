//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellNames.h"
#include "SPSpell.generated.h"

/**
 * 
 */
UCLASS()
class SP_API USPSpell : public UObject
{
	GENERATED_BODY()

	public:

		USPSpell();

		//Spell Name
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
		SpellNames Name;

		//Spell Icon
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
		UTexture2D* Icon;

		//Spell Description
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
		FString Description;

		//Spell Difficulty
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
		float Difficulty;

		//Spell Mana Cost
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
		float ManaCost;

		//Spell Value
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
		float Value;

		//Function to cast the spell
		UFUNCTION(BlueprintCallable, Category = "Spell")
		void CastSpell();

		//Function to upgrade the spell
		UFUNCTION(BlueprintCallable, Category = "Spell")
		void UpgradeSpell();

		//Function to downgrade the spell
		UFUNCTION(BlueprintCallable, Category = "Spell")
		void DowngradeSpell();

		//Function to destroy the spell
		UFUNCTION(BlueprintCallable, Category = "Spell")
		void DestroySpell();

		//Function for combining spells
		UFUNCTION(BlueprintCallable, Category = "Spell")
		void CombineSpell();

		//Technical Discipline level needed to use the spell
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
		int32 TechLevel;

		//Spiritual Discipline level needed to use the spell
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
		int32 SpiritLevel;

		//Endurance Discipline level needed to use the spell
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
		int32 EnduranceLevel;

		//Mechanical Discipline level needed to use the spell
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
		int32 MechanicalLevel;

		//Social Discipline level needed to use the spell
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
		int32 SocialLevel;

	
};
