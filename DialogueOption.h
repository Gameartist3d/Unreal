//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "KnowledgeTopic.h"
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
};
