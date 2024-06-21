//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USocialComponent.h"
#include "Blueprint/UserWidget.h"
#include "InteractionComponent.generated.h"

class UInteractionMenuWidget;

UENUM(BlueprintType)
enum class EInteractionTypes : uint8
{
	Open,
	Pickup,
	Inspect,
	Talk,
	Insert,
	Remove,
	Combine,
	Compare,
	Examine,
	Operate,
	Activate,
	Deactivate,
	Lock,
	Unlock,
	Enter,
	Exit,
	Search,
	Steal,
	Break,
	Repair,
	Upgrade,
	Disassemble,
	Assemble,
	Drink,
	Eat,
	Sit,
	Lay,
	Lounge,
	Order,
	Tap,
	Press,
	Push,
	Pull,
	Turn,
	Flip,
	Slide,
	Spin,
	Throw,
	Place,
	Plant,
	Build,
	Grab,
	Release,
	Shake,
	Equip,
	Ride,
	Drive,
	OperateVehicle,
	Play,
	Close,
	Jack,
	Unjack,
	Connect,
	Disconnect,
	Attach,
	Detach,
	Load,
	Unload,
	Refuel,
	Hack,
	Scan,
	Inject
};

//For pushing updates to the UI

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnactorInteractUpdate, AActor*, interactedactor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemInteractUpdate, ASPBaseItem*, interacteditem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharInteractUpdate, ASPCharacter*, interactedchar);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	// bool to check if the owner has a USocialComponent
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bHasUSocialComponent;

	//bool to check if the component is being interacted with
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bIsBusy = false;

	//Tarray of Enums for the interaction types
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TArray<EInteractionTypes> InteractionTypes;

	//Delegate for interaction updates
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractionUpdated OnInteractionUpdated;

	//Delegate for actor interaction updates
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnactorInteractUpdate OnactorInteractUpdate;

	//Delegate for item interaction updates
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnItemInteractUpdate OnItemInteractUpdate;

	//Delegate for character interaction updates
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnCharInteractUpdate OnCharInteractUpdate;

	//Function for adding an interaction type
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void AddInteractionType(EInteractionTypes InteractionType);

	//Function for removing an interaction type
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void RemoveInteractionType(EInteractionTypes InteractionType);

	//Function for getting the interaction type from a string
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	EInteractionTypes GetInteractionTypeFromString(const FString& InteractionName) const;

	//Function for calling the function based on the supplied interaction type
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void CallInteractionFunction(EInteractionTypes InteractionType);

protected:
	// Called when the game star  ts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*List of Interaction Type overridable Functions If an Actor needs to use one of the interaction types, it can override the functionality in its own bp*/
	//Function for Open Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OpenInteraction();
	virtual void OpenInteraction_Implementation();

	//Function for Pickup Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void PickupInteraction();
	virtual void PickupInteraction_Implementation();

	//Function for Inspect Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void InspectInteraction();
	virtual void InspectInteraction_Implementation();

	//Function for Talk Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void TalkInteraction();
	virtual void TalkInteraction_Implementation();

	//Function for Insert Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void InsertInteraction();
	virtual void InsertInteraction_Implementation();

	//Function for Remove Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void RemoveInteraction();
	virtual void RemoveInteraction_Implementation();

	//Function for Combine Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void CombineInteraction();
	virtual void CombineInteraction_Implementation();

	//Function for Compare Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void CompareInteraction();
	virtual void CompareInteraction_Implementation();

	//Function for Examine Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ExamineInteraction();
	virtual void ExamineInteraction_Implementation();

	//Function for Operate Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OperateInteraction();
	virtual void OperateInteraction_Implementation();

	//Function for Activate Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ActivateInteraction();
	virtual void ActivateInteraction_Implementation();

	//Function for Deactivate Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void DeactivateInteraction();
	virtual void DeactivateInteraction_Implementation();

	//Function for Lock Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void LockInteraction();
	virtual void LockInteraction_Implementation();

	//Function for Unlock Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void UnlockInteraction();
	virtual void UnlockInteraction_Implementation();

	//Function for Enter Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void EnterInteraction();
	virtual void EnterInteraction_Implementation();

	//Function for Exit Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ExitInteraction();
	virtual void ExitInteraction_Implementation();

	//Function for Search Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void SearchInteraction();
	virtual void SearchInteraction_Implementation();

	//Function for Steal Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void StealInteraction();
	virtual void StealInteraction_Implementation();

	//Function for Break Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void BreakInteraction();
	virtual void BreakInteraction_Implementation();

	//Function for Repair Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void RepairInteraction();
	virtual void RepairInteraction_Implementation();

	//Function for Upgrade Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void UpgradeInteraction();
	virtual void UpgradeInteraction_Implementation();

	//Function for Disassemble Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void DisassembleInteraction();
	virtual void DisassembleInteraction_Implementation();

	//Function for Assemble Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void AssembleInteraction();
	virtual void AssembleInteraction_Implementation();

	//Function for Drink Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void DrinkInteraction();
	virtual void DrinkInteraction_Implementation();

	//Function for Eat Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void EatInteraction();
	virtual void EatInteraction_Implementation();

	//Function for Sit Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void SitInteraction();
	virtual void SitInteraction_Implementation();

	//Function for Lay Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void LayInteraction();
	virtual void LayInteraction_Implementation();

	//Function for Lounge Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void LoungeInteraction();
	virtual void LoungeInteraction_Implementation();

	//Function for Order Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OrderInteraction();
	virtual void OrderInteraction_Implementation();

	//Function for Tap Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void TapInteraction();
	virtual void TapInteraction_Implementation();

	//Function for Press Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void PressInteraction();
	virtual void PressInteraction_Implementation();

	//Function for Push Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void PushInteraction();

	//Function for Pull Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void PullInteraction();
	virtual void PullInteraction_Implementation();

	//Function for Turn Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void TurnInteraction();
	virtual void TurnInteraction_Implementation();

	//Function for Flip Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void FlipInteraction();
	virtual void FlipInteraction_Implementation();

	//Function for Slide Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void SlideInteraction();
	virtual void SlideInteraction_Implementation();

	//Function for Spin Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void SpinInteraction();
	virtual void SpinInteraction_Implementation();

	//Function for Throw Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ThrowInteraction();
	virtual void ThrowInteraction_Implementation();

	//Function for Place Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void PlaceInteraction();
	virtual void PlaceInteraction_Implementation();

	//Function for Plant Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void PlantInteraction();
	virtual void PlantInteraction_Implementation();

	//Function for Build Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void BuildInteraction();
	virtual void BuildInteraction_Implementation();

	//Function for Grab Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void GrabInteraction();
	virtual void GrabInteraction_Implementation();

	//Function for Release Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ReleaseInteraction();
	virtual void ReleaseInteraction_Implementation();

	//Function for Shake Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ShakeInteraction();
	virtual void ShakeInteraction_Implementation();

	//Function for Equip Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void EquipInteraction();
	virtual void EquipInteraction_Implementation();

	//Function for Ride Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void RideInteraction();
	virtual void RideInteraction_Implementation();

	//Function for Drive Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void DriveInteraction();
	virtual void DriveInteraction_Implementation();

	//Function for Operate Vehicle Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OperateVehicleInteraction();
	virtual void OperateVehicleInteraction_Implementation();

	//Function for Play Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void PlayInteraction();
	virtual void PlayInteraction_Implementation();

	//Function for Close Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void CloseInteraction();
	virtual void CloseInteraction_Implementation();

	//Function for Jack Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void JackInteraction();
	virtual void JackInteraction_Implementation();

	//Function for Unjack Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void UnjackInteraction();
	virtual void UnjackInteraction_Implementation();

	//Function for Connect Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ConnectInteraction();
	virtual void ConnectInteraction_Implementation();

	//Function for Disconnect Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void DisconnectInteraction();
	virtual void DisconnectInteraction_Implementation();

	//Function for Attach Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void AttachInteraction();
	virtual void AttachInteraction_Implementation();

	//Function for Detach Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void DetachInteraction();
	virtual void DetachInteraction_Implementation();

	//Function for Load Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void LoadInteraction();
	virtual void LoadInteraction_Implementation();

	//Function for Unload Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void UnloadInteraction();
	virtual void UnloadInteraction_Implementation();

	//Function for Refuel Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void RefuelInteraction();
	virtual void RefuelInteraction_Implementation();

	//Function for Hack Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void HackInteraction();
	virtual void HackInteraction_Implementation();

	//Function for Scan Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ScanInteraction();
	virtual void ScanInteraction_Implementation();

	//Function for Inject Interaction
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void InjectInteraction();
	virtual void InjectInteraction_Implementation();

	private: 

		FString GetEnumValueAsString(const FString& name, int32 value) const;
};
