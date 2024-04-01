//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "EKnowledgeFamiliarity.h"
#include "KnowledgeTopic.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class SP_API UKnowledgeTopic : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
	FString TopicName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
	FString TopicDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Topic")
	EKnowledgeFamiliarity KnowledgeFamiliarity;

	UKnowledgeTopic();
	~UKnowledgeTopic();
};
