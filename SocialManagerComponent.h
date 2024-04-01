//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EPrivacyLevel.h"
#include "USocialComponent.h"
#include "DialogueOption.h"
#include "SPCharacter.h"
#include "SocialManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueChoiceUpdated);

USTRUCT(BlueprintType)
struct FDialogueVariables {

	GENERATED_BODY()

	//true if the characters have exchanged greetings
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bHasGreeted;

	//true if the playuur walks away from convo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bHasLeftConvo;

	//true if the playuur is the active talker
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsPlayuurTalking;

	//false if the playuur is present in the conversation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsJustNPCs;

	//if true, characters will focus on the active talker, if not, convo will be more freeform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	bool bIsDialogueOptionLinear;

	//maximum number of dialogue iterations the characters will engage in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	int32 DialogueLimit;

	//the current count of dialogue iterations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =  "Dialogue")
	int32 DialogueCount;

	//the privacy level of the current conversation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	EPrivacyLevel PrivacyLevel;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API USocialManagerComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USocialManagerComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Characters")
	TArray<class ACharacter*> TalkingCharacters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	class ACharacter* ActiveTalkingCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FDialogueVariables DialogueVariables;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<class UDialogueOption*> DialogueOptions;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetDialogueChoice();

	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FOnDialogueChoiceUpdated OnDialogueChoiceUpdated;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void GiveTopicKnowledge(TArray<class UKnowledgeTopic*> Topics, class ACharacter* Character);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetConversationActive(bool bActive);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void AddTalkingCharacter(class ACharacter* TalkingCharacter);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetActiveTalkingCharacter(class ACharacter* ActiveCharacter);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void RemoveTalkingCharacter(class ACharacter* TalkingCharacter);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void AddDialogueOption(class UDialogueOption* Topic);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void RemoveDialogueOption(class UDialogueOption* Topic);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	bool IsConversationActive = true;
		
};
