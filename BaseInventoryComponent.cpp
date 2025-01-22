//3DNomad LLC


#include "BaseInventoryComponent.h"
#include "DefaultCharacter.h"

// Sets default values for this component's properties
UBaseInventoryComponent::UBaseInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	PrimaryComponentTick.bCanEverTick = true;
	OwnerCharacter = Cast<ADefaultCharacter>(GetOwner());
}

// Called when the game starts
void UBaseInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UBaseInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

