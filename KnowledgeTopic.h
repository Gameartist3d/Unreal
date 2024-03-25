//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "EKnowledgeFamiliarity.h"
#include "KnowledgeTopic.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SP_API KnowledgeTopic
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
	FString TopicName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
	FString TopicDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<class FString> DialogueNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
	EKnowledgeFamiliarity KnowledgeFamiliarity;

	KnowledgeTopic();
	~KnowledgeTopic();
};
