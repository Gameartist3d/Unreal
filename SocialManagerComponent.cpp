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

//TODO Add interaction to dialogue options and then set the next active talker
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

void USocialManagerComponent::GiveTopicKnowledge(TArray<class UKnowledgeTopic*> Topics, class ACharacter* Character) {
	
	for (auto foundcharacter : TalkingCharacters) {
		if(foundcharacter == Character){
			UUSocialComponent* SocialComponent = Cast<UUSocialComponent>(foundcharacter->GetComponentByClass(UUSocialComponent::StaticClass()));
			if (SocialComponent){
				for (auto foundtopic : Topics) {
					SocialComponent->AddDialogueTopic(foundtopic);
				}
			}
		}
	}
}
//TODO add a function to add local characters that would be interested in the convo
void USocialManagerComponent::AddTalkingCharacter(class ACharacter* TalkingCharacter) {

	TalkingCharacters.Add(TalkingCharacter);
}

void USocialManagerComponent::SetActiveTalkingCharacter(class ACharacter* ActiveCharacter) {

	ActiveTalkingCharacter = ActiveCharacter;
}

// Called every frame
void USocialManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

