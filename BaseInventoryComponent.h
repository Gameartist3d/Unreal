//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EItemSlot.h"
#include "BaseInventoryComponent.generated.h"



//For updating the UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemSlotUpdated, EItemSlot, SlotChanged);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPV1_API UBaseInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	/*Variables*/

	/*Functions*/

	/*Overrides*/

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	/*Variables*/

	//Variable to store owner character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	class ADefaultCharacter* OwnerCharacter;

	//Delegate for updating slot with ESPEquipmentSlot provided
	UPROPERTY(BlueprintAssignable, Category = "Weapon")
	FOnItemSlotUpdated OnSlotUpdated;

	/*Functions*/

	// Sets default values for this component's properties
	UBaseInventoryComponent();
	
	/*Overrides*/

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
