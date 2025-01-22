//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Outfit.generated.h"

UCLASS()
class SPV1_API AOutfit : public AActor
{
	GENERATED_BODY()
	
public:	

	/*Variables*/

	//Variable for the Outfit name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outfit")
	FName OutfitName = TEXT("Outfit");

	//Color variable based on the Armor Rarity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outfit")
	FLinearColor ArmorRarityColor = FLinearColor::White;

	//Color variable based on the Shield Rarity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Outfit")
	FLinearColor ShieldRarityColor = FLinearColor::White;

	/*Functions*/

	// Sets default values for this actor's properties
	AOutfit();

	/*Overrides*/

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	/*Variables*/

	/*Functions*/

	/*Overrides*/

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
