//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SocialManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueChoiceUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API USocialManagerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USocialManagerComponent();

	UPROPERTY(EditAnywhere, Category = "Characters")
	TArray<class ACharacter*> TalkingCharacters;

	/*TODO UPROPERTY(EditAnywhere, Category = "Dialogue")
	UDialogueOption DialogueOption;*/

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetDialogueChoice();

	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FOnDialogueChoiceUpdated OnDialogueChoiceUpdated;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void GiveTopicKnowledge(TArray<class AKnowledgeTopic*> Topics, class ACharacter* Character);

	void SetConversationActive(bool bActive);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	bool IsConversationActive = true;
		
};
