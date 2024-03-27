//3DNomad LLC


#include "USocialComponent.h"

// Sets default values for this component's properties
UUSocialComponent::UUSocialComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UUSocialComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

//Add Dialogue Topic
void UUSocialComponent::AddDialogueTopic(class UKnowledgeTopic* Topic) {
	DialogueTopics.Add(Topic);
}

//Remove Dialogue Topic
void UUSocialComponent::RemoveDialogueTopic(class UKnowledgeTopic* Topic) {
	DialogueTopics.Remove(Topic);
}

// Called every frame
void UUSocialComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

