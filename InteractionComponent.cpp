//3DNomad LLC


#include "InteractionComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SceneComponent.h"
#include "GameFramework/HUD.h"
#include "Misc/OutputDeviceNull.h"
#include "Engine/Engine.h"
#include "UObject/UnrealType.h"
#include "InteractionMenuWidget.h"
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bHasUSocialComponent = false;
	// ...
}
void UInteractionComponent::AddInteractionType(EInteractionTypes InteractionType)
{
	InteractionTypes.Add(InteractionType);
    OnInteractionUpdated.Broadcast();
}

void UInteractionComponent::RemoveInteractionType(EInteractionTypes InteractionType)
{
	InteractionTypes.Remove(InteractionType);
    OnInteractionUpdated.Broadcast();
}

EInteractionTypes UInteractionComponent::GetInteractionTypeFromString(const FString& InteractionName) const
{
	return EInteractionTypes();
}

FString UInteractionComponent::GetEnumValueAsString(const FString& Name, int32 Value) const
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr)
	{
		return FString("Invalid");
	}

	return EnumPtr->GetNameStringByIndex(Value);
}
void UInteractionComponent::CallInteractionFunction(EInteractionTypes InteractionType)
{
	if (InteractionTypes.Contains(InteractionType)) {
		FString functionnamestring = GetEnumValueAsString(TEXT("EInteractionType"), static_cast<int32>(InteractionType));
		FName functionname(*functionnamestring);
		FOutputDeviceNull outputdevice;
		this->CallFunctionByNameWithArguments(*functionname.ToString(), outputdevice, nullptr, true);
	}
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner) {
		UUSocialComponent* socialcomponent = Cast<UUSocialComponent>(Owner->GetComponentByClass(UUSocialComponent::StaticClass()));
		if (socialcomponent) {
			bHasUSocialComponent = true;
		}
		else {
			bHasUSocialComponent = false;
		}
	}

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionComponent::OpenInteraction_Implementation()
{
}

void UInteractionComponent::PickupInteraction_Implementation()
{
}

void UInteractionComponent::InspectInteraction_Implementation()
{
}

void UInteractionComponent::TalkInteraction_Implementation()
{
}

void UInteractionComponent::InsertInteraction_Implementation()
{
}

void UInteractionComponent::RemoveInteraction_Implementation()
{
}

void UInteractionComponent::CombineInteraction_Implementation()
{
}

void UInteractionComponent::CompareInteraction_Implementation()
{
}

void UInteractionComponent::ExamineInteraction_Implementation()
{
}

void UInteractionComponent::OperateInteraction_Implementation()
{
}

void UInteractionComponent::ActivateInteraction_Implementation()
{
}

void UInteractionComponent::DeactivateInteraction_Implementation()
{
}

void UInteractionComponent::LockInteraction_Implementation()
{
}

void UInteractionComponent::UnlockInteraction_Implementation()
{
}

void UInteractionComponent::EnterInteraction_Implementation()
{
}

void UInteractionComponent::ExitInteraction_Implementation()
{
}

void UInteractionComponent::SearchInteraction_Implementation()
{
}

void UInteractionComponent::StealInteraction_Implementation()
{
}

void UInteractionComponent::BreakInteraction_Implementation()
{
}

void UInteractionComponent::RepairInteraction_Implementation()
{
}

void UInteractionComponent::UpgradeInteraction_Implementation()
{
}

void UInteractionComponent::DisassembleInteraction_Implementation()
{
}

void UInteractionComponent::AssembleInteraction_Implementation()
{
}

void UInteractionComponent::DrinkInteraction_Implementation()
{
}

void UInteractionComponent::EatInteraction_Implementation()
{
}

void UInteractionComponent::SitInteraction_Implementation()
{
}

void UInteractionComponent::LayInteraction_Implementation()
{
}

void UInteractionComponent::LoungeInteraction_Implementation()
{
}

void UInteractionComponent::OrderInteraction_Implementation()
{
}

void UInteractionComponent::TapInteraction_Implementation()
{
}

void UInteractionComponent::PressInteraction_Implementation()
{
}

void UInteractionComponent::PushInteraction_Implementation()
{
}

void UInteractionComponent::PullInteraction_Implementation()
{
}

void UInteractionComponent::TurnInteraction_Implementation()
{
}

void UInteractionComponent::FlipInteraction_Implementation()
{
}

void UInteractionComponent::SlideInteraction_Implementation()
{
}

void UInteractionComponent::SpinInteraction_Implementation()
{
}

void UInteractionComponent::ThrowInteraction_Implementation()
{
}

void UInteractionComponent::PlaceInteraction_Implementation()
{
}

void UInteractionComponent::PlantInteraction_Implementation()
{
}

void UInteractionComponent::BuildInteraction_Implementation()
{
}

void UInteractionComponent::GrabInteraction_Implementation()
{
}

void UInteractionComponent::ReleaseInteraction_Implementation()
{
}

void UInteractionComponent::ShakeInteraction_Implementation()
{
}

void UInteractionComponent::EquipInteraction_Implementation()
{
}

void UInteractionComponent::RideInteraction_Implementation()
{
}

void UInteractionComponent::DriveInteraction_Implementation()
{
}

void UInteractionComponent::OperateVehicleInteraction_Implementation()
{
}

void UInteractionComponent::PlayInteraction_Implementation()
{
}

void UInteractionComponent::CloseInteraction_Implementation()
{
}

void UInteractionComponent::JackInteraction_Implementation()
{
}

void UInteractionComponent::UnjackInteraction_Implementation()
{
}

void UInteractionComponent::ConnectInteraction_Implementation()
{
}

void UInteractionComponent::DisconnectInteraction_Implementation()
{
}

void UInteractionComponent::AttachInteraction_Implementation()
{
}

void UInteractionComponent::DetachInteraction_Implementation()
{
}

void UInteractionComponent::LoadInteraction_Implementation()
{
}

void UInteractionComponent::UnloadInteraction_Implementation()
{
}

void UInteractionComponent::RefuelInteraction_Implementation()
{
}

void UInteractionComponent::HackInteraction_Implementation()
{
}

void UInteractionComponent::ScanInteraction_Implementation()
{
}

void UInteractionComponent::InjectInteraction_Implementation()
{
}
