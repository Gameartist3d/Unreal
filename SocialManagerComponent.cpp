//3DNomad LLC


#include "SocialManagerComponent.h"

// Sets default values for this component's properties
USocialManagerComponent::USocialManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USocialManagerComponent::SetDialogueChoice()
{
	OnDialogueChoiceUpdated.Broadcast();
}

void USocialManagerComponent::SetConversationActive(bool bActive) {
	
	IsConversationActive = bActive;
}

// Called when the game starts
void USocialManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
//TODO create a universal social component that all characters share so that this function can just reference that component.
void USocialManagerComponent::GiveTopicKnowledge(TArray<class AKnowledgeTopic*> Topics, class ACharacter* Character) {
	
	for (auto foundcharacter : TalkingCharacters) {
		if(foundcharacter == Character){
//TODO reference the component here and add topics.
			return;
		}
	}
}


// Called every frame
void USocialManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
