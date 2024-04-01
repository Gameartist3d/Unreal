//3DNomad LLC
 
#pragma once

#include "CoreMinimal.h"
#include "KnowledgeTopic.h"
#include "ESPSkillNames.h"
#include "DialogueOption.generated.h"

UENUM(BlueprintType)
enum class EDialogueCategory : uint8
{
	General UMETA(DisplayName = "General"),
	Mission UMETA(DisplayName = "Mission"),
	Personal UMETA(DisplayName = "Personal"),
	Stats UMETA(DisplayName = "Stats"),
	Misc UMETA(DisplayName = "Misc")
};

USTRUCT(BlueprintType)
struct FDialogueChoices
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FText DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TMap<ESPSkillNames, int32> DialogueSkillCheck;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	EKnowledgeFamiliarity DialogueKnowledgeCheck;

	
};

UCLASS(Blueprintable)
class SP_API UDialogueOption : public UObject
{
	GENERATED_BODY()

public:

	UDialogueOption();

	~UDialogueOption();

	//Category for splitting up dialogue options
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	EDialogueCategory DialogueCategory;

	//Knowledge Topic for the dialogue option
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UKnowledgeTopic* KnowledgeTopic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FString> DialogueNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FDialogueChoices> DialogueChoices;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void AddDialogueChoice(FDialogueChoices DialogueChoice);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void RemoveDialogueChoice(FDialogueChoices DialogueChoice);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void AddDialogueName(FString DialogueName);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void RemoveDialogueName(FString DialogueName);
};
