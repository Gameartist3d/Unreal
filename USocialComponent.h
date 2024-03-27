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

	void AddDialogueTopic(class UKnowledgeTopic* Topic);
	void RemoveDialogueTopic(class UKnowledgeTopic* Topic);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Dialogue")
	TArray<class UKnowledgeTopic*> DialogueTopics;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
