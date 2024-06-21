// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SPGameMode.generated.h"

UCLASS(minimalapi)
class ASPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASPGameMode();

	virtual void PawnKilled(APawn* killedpawn);
};


