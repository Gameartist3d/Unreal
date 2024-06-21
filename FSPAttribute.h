//3DNomad LLC

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

	 FSPAttribute()
		 : AttributeName(EAttributeName::Physical),
		 AttributeLvl(1),
		 AttributeExp(0.0f),
		 AttributeIcon(nullptr)
	 {

	 }

	 FSPAttribute(EAttributeName name, int32 lvl, float exp, UTexture2D* icon)
		 : AttributeName(name),
		 AttributeLvl(lvl),
		 AttributeExp(exp),
		 AttributeIcon(icon)
	 {
	 }
};
