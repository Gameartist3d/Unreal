//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellData.h"
#include "Spell.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SPV1_API USpell : public UObject
{
	GENERATED_BODY()

public:
/*variables*/
	
	UPROPERTY(EditAnywhere, Category = "SpellData")
	FSpellTextData SpellTextData;

	UPROPERTY(EditAnywhere, Category = "SpellData")
	FSpellNumericData SpellNumericData;

	UPROPERTY(EditAnywhere, Category = "SpellData")
	FSpellAssetData SpellAssetData;

	/*functions*/

	USpell();
	
	//function for prepping the spell
	UFUNCTION(BlueprintCallable)
	virtual void ChannelSpell(AActor* Caster);

	//function for when the channeling stutters
	UFUNCTION(BlueprintCallable)
	virtual void OnChannelStutter(AActor* Caster);

	//function for when the channeling fails
	UFUNCTION(BlueprintCallable)
	virtual void OnChannelFail(AActor* Caster);

	//function for casting the spell
	UFUNCTION(BlueprintCallable)
	virtual void CastSpell(AActor* Caster);

	//function for when the spell fails
	UFUNCTION(BlueprintCallable)
	virtual void SpellCastFail(AActor* Caster);
};
