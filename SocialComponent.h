//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SocialComponent.generated.h"

//Enum for Historical Responses
UENUM(BlueprintType)
enum class EHistoricalResponse : uint8
{
	None UMETA(DisplayName = "None"),
	DisagreedA UMETA(DisplayName = "DisagreedA"),
	DisagreedB UMETA(DisplayName = "DisagreedB"),
	DisagreedC UMETA(DisplayName = "DisagreedC"),
	AgreedA UMETA(DisplayName = "Agreed"),
	AgreedB UMETA(DisplayName = "AgreedB"),
	AgreedC UMETA(DisplayName = "AgreedC"),
	CompromiseA UMETA(DisplayName = "CompromiseA"),
	CompromiseB UMETA(DisplayName = "CompromiseB"),
	CompromiseC UMETA(DisplayName = "CompromiseC")
};

//Enum for Emotion Types
UENUM(BlueprintType)
enum class EEmotionType : uint8
{
	None UMETA(DisplayName = "None"),
	Anger UMETA(DisplayName = "Anger"),
	Disgust UMETA(DisplayName = "Disgust"),
	Fear UMETA(DisplayName = "Fear"),
	Happiness UMETA(DisplayName = "Happiness"),
	Sadness UMETA(DisplayName = "Sadness"),
	Surprise UMETA(DisplayName = "Surprise")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPV1_API USocialComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/*Variables*/

	//TMap for Historical Responses
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EHistoricalResponse, FString> HistoricalResponses;

	//TMap for the character's current emotions
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<EEmotionType, float> CurrentEmotion;

	//Bool for if the character is currently in a conversation
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInConversation;

	/*Functions*/
	// Sets default values for this component's properties
	USocialComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
