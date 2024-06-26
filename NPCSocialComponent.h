//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SPCharacter.h"
#include "USocialComponent.h"
#include "NPCSocialComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SP_API UNPCSocialComponent : public UUSocialComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNPCSocialComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playuur")
	ASPCharacter* TalkingPlayuur;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCSocial")
	float MaxDistanceToTalk = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCSocial")
	float MinDistanceToTalk = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCSocial")
	float MaxWaitTime = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCSocial")
	bool bCanTalk = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCSocial")
	bool bIsTalking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCSocial")
	bool bIsFocusedonPlayuur = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
