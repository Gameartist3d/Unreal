//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatsPanelWidget.generated.h"

class UStatsAttributeWidget;
struct FGeometry;
/**
 * 
 */
UCLASS()
class SPV1_API UStatsPanelWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//Widget class to spawn attribute widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UStatsAttributeWidget> AttributeWidgetClass;

protected:
/*variables*/
	//Panel for storing Attribute widgets
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* AttributeWidgetBox; 

	//Panel for storing Discipline widgets
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* DisciplineWidgetBox; 

	//Box for storing Skill widgets
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* SkillFill01Box;

	//Box for storing Skill widgets
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* SkillFill02Box;

	//Box for storing Skill widgets
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* SkillFill03Box;

	//Box for storing Skill widgets
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* SkillFill04Box; 
	/*overrides*/
	
	virtual void NativeOnInitialized() override;
	
};
