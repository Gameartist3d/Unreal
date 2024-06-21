//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SPBaseItem.h"
#include "SPCharacter.h"
#include "InteractionMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SP_API UInteractionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//function for activating the focused interaction box
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void ActivateFocusedInteractionBox(UInteractionComponent* interactcomp);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void SendItemInfo2Menu(ASPBaseItem* itemtointeract, UInteractionComponent* iteminteractcomp);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interaction")
	void SendCharInfo2Menu(ASPCharacter* chartointeract, UInteractionComponent* charinteractcomp);

	//Name of item being interacted with
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemInfo")
	FText ItemName;
	
	//item rarity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	ESPItemRarity ItemRarity;

	//description of the item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	//weight of the item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float ItemWeight;

	//Tmap of currencies used to evaluate the value of the item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0f))
	TMap<ESPCurrency, float> ItemValue;

	//bool to check if item is owned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bIsOwned;

	//Interaction component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UInteractionComponent* InteractionComponent;

	//Tarray of Enums for the interaction types
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TArray<EInteractionTypes> InteractionTypes;

	/*
	* 
	CHARACTER INFO
	*
	*/

	//character's level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 CharacterLevel;

	//character's name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FText CharacterName;

};
