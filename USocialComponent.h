//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KnowledgeTopic.h"
#include "USocialComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogueOptionsUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API UUSocialComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUSocialComponent();

	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FDialogueOptionsUpdated DialogueOptionsUpdated; 

	UFUNCTION(BlueprintCallable, Category = "Topics")
	void AddTopic(FString Topic, EKnowledgeFamiliarity Familiarity);

	UFUNCTION(BlueprintCallable, Category = "Topics")
	EKnowledgeFamiliarity GetTopicFamiliarity(FString Topic);

	UFUNCTION(BlueprintCallable, Category = "Topics")
	void SetTopicFamiliarity(FString Topic, EKnowledgeFamiliarity Familiarity);

	UFUNCTION(BlueprintCallable, Category = "Topics")
	void RemoveTopic(FString Topic);

	UFUNCTION(BlueprintCallable, Category = "NPCSocial")
	void StartDialogue(AActor* Interactor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Dialogue")
	TMap<FString, EKnowledgeFamiliarity> TopicKnowledge;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
