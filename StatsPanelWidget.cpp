//3DNomad LLC

#include "StatsPanelWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "StatsAttributeWidget.h"
#include "PlayerStatsComponent.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"

void UStatsPanelWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	APlayerController* OwningPC = GetOwningPlayer();
	if (!OwningPC)
	{
		UE_LOG(LogTemp, Error, TEXT("UStatsPanelWidget::NativeOnInitialized::Player controller Cast failed! whugh"));
		return;
	}

	const APawn* OwningPawn = OwningPC->GetPawn();
	if (!OwningPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("UStatsPanelWidget::NativeOnInitialized::GetPawn() Failed? Just pack up bruh"));
		return;
	}

	UPlayerStatsComponent* StatsComp = OwningPawn->FindComponentByClass<UPlayerStatsComponent>();
	if (!StatsComp)
	{
		UE_LOG(LogTemp, Error, TEXT("UStatsPanelWidget::NativeOnInitialized: StatsComponent Cast fails"));
		return;
	}
	
	if (AttributeWidgetClass && AttributeWidgetBox)
	{
		for (const FAttribute& Attr : StatsComp->GetSPAttributes())
		{
			UStatsAttributeWidget* NewWidget = CreateWidget<UStatsAttributeWidget>(GetWorld(), AttributeWidgetClass);
			if (NewWidget)
			{
				//Set UI Elements
				NewWidget->SetSPAttributeData(Attr);
				
				// Add widget to intended horizontalbox
				UHorizontalBoxSlot* NewSlot = AttributeWidgetBox->AddChildToHorizontalBox(NewWidget);
				
				if (NewSlot)
				{
					NewSlot->SetPadding(FMargin(20.0f, 5.0f, 20.0f, 5.0f));
					NewSlot->SetHorizontalAlignment(HAlign_Left);
					NewSlot->SetVerticalAlignment(VAlign_Center);
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("Added an attribute successfully"));
		}
	}
	
	if (AttributeWidgetClass && DisciplineWidgetBox)
	{
		for (const FDiscipline& Disc : StatsComp->GetDisciplines())
		{
			UStatsAttributeWidget* NewWidget = CreateWidget<UStatsAttributeWidget>(GetWorld(), AttributeWidgetClass);
			if (NewWidget)
			{
				NewWidget->SetDisciplineData(Disc);
				UHorizontalBoxSlot* NewSlot = DisciplineWidgetBox->AddChildToHorizontalBox(NewWidget);
				if (NewSlot)
				{
					NewSlot->SetPadding(FMargin(5.0f));
				}
			}
		}
	}
	
	if (AttributeWidgetClass && StatsComp)
	{
		TArray<UHorizontalBox*> Boxes;
		Boxes.Add(SkillFill01Box);
		Boxes.Add(SkillFill02Box);
		Boxes.Add(SkillFill03Box);
		Boxes.Add(SkillFill04Box);

		const TArray<FSkill>& AllSkills = StatsComp->GetSkills();

		for (int32 i = 0; i < AllSkills.Num(); ++i)
		{
			UStatsAttributeWidget* NewWidget = CreateWidget<UStatsAttributeWidget>(GetWorld(), AttributeWidgetClass);
			if (NewWidget)
			{
				NewWidget->SetSkillData(AllSkills[i]);
				
				int32 BoxIndex = i / 6; 
				if (Boxes.IsValidIndex(BoxIndex))
				{
					UHorizontalBoxSlot* NewSlot = Boxes[BoxIndex]->AddChildToHorizontalBox(NewWidget);
					if (NewSlot)
					{
						NewSlot->SetPadding(FMargin(5.0f));
					}
				}
			}
		}
	}
}



