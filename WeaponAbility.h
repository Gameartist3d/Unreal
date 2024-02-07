#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponAbility.generated.h"


UCLASS( Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), DefaultToInstanced )
class SP_API UWeaponAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponAbility();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability")
	FText AbilityName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	class UTexture2D* AbilityIcon;

	//BP implementation
	UFUNCTION(BlueprintNativeEvent, Category = "Ability")
	void UseWeaponAbility();

	virtual void UseWeaponAbility_Implementation(){}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


		
};
