//3DNomad LLC
#pragma once

#include "CoreMinimal.h"
#include "SPGameMode.h"
#include "SPSinglePlayerMode.generated.h"

/**
 * 
 */
UCLASS()
class SP_API ASPSinglePlayerMode : public ASPGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* killedpawn) override;
};
