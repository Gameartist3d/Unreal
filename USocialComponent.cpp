//3DNomad LLC


#include "USocialComponent.h"

// Sets default values for this component's properties
UUSocialComponent::UUSocialComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UUSocialComponent::AddTopic(FString Topic, EKnowledgeFamiliarity Familiarity)
{
	if (!TopicKnowledge.Contains(Topic)) {
		TopicKnowledge.Add(Topic, Familiarity);
	}
}

EKnowledgeFamiliarity UUSocialComponent::GetTopicFamiliarity(FString Topic)
{
	if (TopicKnowledge.Contains(Topic)) {
		return TopicKnowledge[Topic];
	}
	else
{
	return EKnowledgeFamiliarity();
}
}


void UUSocialComponent::SetTopicFamiliarity(FString Topic, EKnowledgeFamiliarity Familiarity)
{
	if (TopicKnowledge.Contains(Topic)) {
		TopicKnowledge[Topic] = Familiarity;
	}
	else {
		TopicKnowledge.Add(Topic, Familiarity);
}
}

void UUSocialComponent::RemoveTopic(FString Topic)
{
	if (TopicKnowledge.Contains(Topic)) {
		TopicKnowledge.Remove(Topic);
	}
}

// Called when the game starts
void UUSocialComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void UUSocialComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

