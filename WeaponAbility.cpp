#include "WeaponAbility.h"

// Sets default values for this component's properties
UWeaponAbility::UWeaponAbility()
{
	AbilityName = FText::FromString(TEXT("Ability"));
}


// Called when the game starts
void UWeaponAbility::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
