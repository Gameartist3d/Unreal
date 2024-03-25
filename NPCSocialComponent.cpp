//3DNomad LLC


#include "NPCSocialComponent.h"

// Sets default values for this component's properties
UNPCSocialComponent::UNPCSocialComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UNPCSocialComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UNPCSocialComponent::AddDialogueTopic(class AKnowledgeTopic* Topic) {
	DialogueTopics.Add(Topic);
}

void UNPCSocialComponent::RemoveDialogueTopic(class AKnowledgeTopic* Topic) {
	DialogueTopics.Remove(Topic);
}


// Called every frame
void UNPCSocialComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
