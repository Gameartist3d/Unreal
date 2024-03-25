//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPCharacter.h"
#include "KnowledgeTopic.h"
#include "NPCSocialComponent.generated.h"

//TODO make class inherit from DEFAULT social component class
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API UNPCSocialComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNPCSocialComponent();

	UPROPERTY(EditAnywhere, Category = "Playuur")
	ASPCharacter* TalkingPlayuur;

	UPROPERTY(EditAnywhere, Category = "Dialogue")
	TArray<class AKnowledgeTopic*> DialogueTopics;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void AddDialogueTopic(class AKnowledgeTopic* Topic);
	void RemoveDialogueTopic(class AKnowledgeTopic* Topic);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
