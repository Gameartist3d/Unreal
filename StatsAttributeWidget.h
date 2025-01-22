//3DNomad LLC
#pragma once

//engine includes
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatsAttributeWidget.generated.h"

enum class ESkillName : uint8;
enum class EDisciplineName : uint8;
enum class EAttributeName : uint8;
struct FSkill;
struct FDiscipline;
struct FAttribute;
class UImage;
class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SPV1_API UStatsAttributeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/*variables*/
	//Text box for the Name 
	UPROPERTY(VisibleAnywhere, Category = "Stats", meta=(BindWidget))
	TObjectPtr<UTextBlock>StatsNameTextBox;

	//Image Icon for the Stat 
	UPROPERTY(VisibleAnywhere, Category = "Stats", meta=(BindWidget))
	TObjectPtr<UImage>StatsIcon;
	
	//Text box for the level 
	UPROPERTY(VisibleAnywhere, Category = "Stats", meta=(BindWidget))
	TObjectPtr<UTextBlock>LevelTextBox;

	//ProgressBar that uses a float for progress 
	UPROPERTY(VisibleAnywhere, Category = "Stats", meta=(BindWidget))
	TObjectPtr<UProgressBar>LevelProgressBar;

	/*functions*/

	//Function for reading data from an FAttribute
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetSPAttributeData(FAttribute NewAttribute);

	//Function for reading data from an FDiscipline
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetDisciplineData(FDiscipline NewDiscipline);

	//Function for reading data from an FSkill
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetSkillData(FSkill NewSkill);
	
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetLevelTextBox(const FText NewLevel) const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetIconTexture(UTexture2D* NewTexture) const;

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void SetLevelProgressBar(const float NewPercent) const;
	void SetStatsNameTextBox(const FText& NewStatsName) const;

private:

	FText GetAttributeEnumText(EAttributeName IncomingAttribute) const;
	FText GetDisciplineEnumText(EDisciplineName IncomingDiscipline) const;
	FText GetSkillEnumText(ESkillName IncomingSkill) const;
};
