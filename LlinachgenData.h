//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LlinachgenData.generated.h"

/**
 * 
 */

//Enum for the different Llinachgen names
UENUM(BlueprintType)
enum class ELlinachgenName : uint8
{
	HueMan UMETA(DisplayName = "HueMan"),
	HueWoa UMETA(DisplayName = "HueWoa"),
	FaiRon UMETA(DisplayName = "FaiRon"),
	FaiRia UMETA(DisplayName = "FaiRia"),
	RowBot UMETA(DisplayName = "ROWBot"),
	WoeDroid UMETA(DisplayName = "WoeDroid"),
	Coleo UMETA(DisplayName = "ColeoPteran"),
	AspBeck UMETA(DisplayName = "AspBeck"),
	SharKin UMETA(DisplayName = "SharKin")
	
};

USTRUCT()
struct FLlinachgenTextData
{
	GENERATED_BODY()
	
	//Llinachgen Name
	UPROPERTY(EditAnywhere, Category = "TextData")
	ELlinachgenName LlinachgenName;

	//Llinachgen Description
	UPROPERTY(EditAnywhere, Category = "TextData")
	FText LlinachgenDescription;
	
};

USTRUCT()
struct FLlinachgenData : public FTableRowBase
{
	GENERATED_BODY()
	
	FLlinachgenTextData LlinachgenTextData;
	
};
