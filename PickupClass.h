//3DNomad LLC

#pragma once
//engine includes
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
//SP includes
#include "InteractionInterface.h"
#include "PickupClass.generated.h"
//SP forward declarations
class USPItem;
//engine forward declarations
class UDataTable;

UCLASS()
class SPV1_API APickupClass : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

public:	

	/*functions*/
	
	// Sets default values for this actor's properties
	APickupClass();

	void InitializePickup(const int32 InQuantity);

	void InitializeDrop(USPItem* DropItem, const int32 DropQuantity);

	FORCEINLINE USPItem* GetItemData() const {return ItemReference;}
	
	/*overrides*/

	
	virtual void BeginFocus() override;
	
	virtual void EndFocus() override;

	UFUNCTION()
	virtual void Interact(APlayerCharacter* Character) override;
	
protected:
	
	/*variables*/
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PickupMesh;

	/**
	 * 
	 */
	UPROPERTY(EditInstanceOnly)
	FDataTableRowHandle ItemRowHandle;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USPItem> ItemReference;

	UPROPERTY(EditInstanceOnly)
	int32 ItemQuantity;

	UPROPERTY(VisibleAnywhere)
	FInteractableData InstanceInteractableData;

	/*functions*/

	void UpdateInteractableData();
	
	UFUNCTION()
	void TakePickup(const APlayerCharacter* Taker);
	
	/*overrides*/
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
