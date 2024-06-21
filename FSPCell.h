//3DNomad LLC
#pragma once

#include "CoreMinimal.h"
#include "FSPCell.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSPCell
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FVector CellPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellType")
	int CellType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellType")
	int CellnDoors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellType")
	int CellnTreasure;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellType")
	int CellnWindows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellType")
	bool CellhasExit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CellType")
	bool CellhasCeiling;
};
