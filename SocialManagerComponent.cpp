//3DNomad LLC


#include "SocialManagerComponent.h"

// Sets default values for this component's properties
USocialManagerComponent::USocialManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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

void USocialManagerComponent::AddDialogueOption(class UDialogueOption* Topic) {
	
	DialogueOptions.Add(Topic);
}

void USocialManagerComponent::RemoveDialogueOption(UDialogueOption* Topic)
{
	DialogueOptions.Remove(Topic);
}

void USocialManagerComponent::GiveTopicKnowledge(TArray<class UKnowledgeTopic*> Topics, class ACharacter* Character) {
	
	for (auto foundcharacter : TalkingCharacters) {
		if(foundcharacter == Character){
			UUSocialComponent* SocialComponent = Cast<UUSocialComponent>(foundcharacter->GetComponentByClass(UUSocialComponent::StaticClass()));
			if (SocialComponent){
				for (auto foundtopic : Topics) {
					SocialComponent->AddTopic(foundtopic->TopicName, foundtopic->KnowledgeFamiliarity);
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

void USocialManagerComponent::RemoveTalkingCharacter(ACharacter* TalkingCharacter)
{
	TalkingCharacters.Remove(TalkingCharacter);
}

// Called every frame
void USocialManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

