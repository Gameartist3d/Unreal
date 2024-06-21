//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ESPCurrency.h"
#include "ESPItemType.h"
#include "ESPItemRarity.h"
#include "ESPEquipmentSlot.h"
#include "InteractionComponent.h"
#include "SPBaseItem.generated.h"

UCLASS()
class SP_API ASPBaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASPBaseItem();

	UPROPERTY(Transient)
	class UWorld* World;

	//mesh to display when item is placed or dropped in the world
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UStaticMeshComponent* PickupMesh;

	//name of item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ItemDisplayName;

	//item type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	ESPItemType ItemType;

	//item rarity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	ESPItemRarity ItemRarity;

	//TArray of slots that the item can be equipped 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<ESPEquipmentSlot> ItemSlots;

	//Interaction component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UInteractionComponent* InteractionComponent;

	//description of the item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	//weight of the item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0))
	float ItemWeight;

	//Tmap of currencies used to evaluate the value of the item
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0f))
	TMap<ESPCurrency, float> ItemValue;

	UPROPERTY()
	class UInventoryComponent* OwnerInventory;

	//bool to check if item is owned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	bool bIsOwned;

	virtual void Use(class ASPCharacter* Character) PURE_VIRTUAL(ASPBaseItem, );

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class ASPCharacter* Character);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
