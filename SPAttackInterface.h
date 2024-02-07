#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FSPDamageType.h"
#include "FHealthVariables.h"
#include "SPAttackInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class USPAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SP_API ISPAttackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(Blueprintable, BlueprintImplementableEvent, Category = "TakeDamage")
	void takeDamage(); 

	UFUNCTION(Blueprintable, BlueprintImplementableEvent, Category = "Attack")
	void attackBody();
};
