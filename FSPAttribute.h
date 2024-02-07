#pragma once

#include "CoreMinimal.h"
#include "EAttributeName.h"
#include "FSPAttribute.generated.h"


 
	USTRUCT(BlueprintType)
	struct FSPAttribute
{
		GENERATED_BODY()
		 
public:

	 UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attribute")
	 EAttributeName AttributeName;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	 int32 AttributeLvl;

	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	 float AttributeExp;

	 UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute")
	 class UTexture2D* AttributeIcon;

	
};
