//3DNomad LLC

//SP includes
#include "SPInteractionMenuWidget.h"
#include "PlayerCharacter.h"
//engine includes
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void USPInteractionMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InteractionProgressBar->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void USPInteractionMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	KeypressText->SetText(FText::FromString(TEXT("Press")));
	CurrentInteractionDuration = 0.0f;
}

void USPInteractionMenuWidget::UpdateInteractionMenu(const FInteractableData* InteractableData) const
{
	switch (InteractableData->InteractionType)
	{
	case EInteractionType::Item:
		KeypressText->SetText(FText::FromString(TEXT("Pickup")));
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		if (InteractableData->Quantity < 2)
		{ 
			QuantityText->SetVisibility(ESlateVisibility::Collapsed);
		}
		else
		{
			QuantityText->SetText(FText::Format(NSLOCTEXT("InteractionWidget", "QuantityText", "x{0}"), InteractableData->Quantity));
			QuantityText->SetVisibility(ESlateVisibility::Visible);
		}
		break;
	case EInteractionType::Character:
		KeypressText->SetText(FText::FromString(TEXT("Social")));
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EInteractionType::Prop:
		KeypressText->SetText(FText::FromString(TEXT("Interact")));
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EInteractionType::Vehicle:
		KeypressText->SetText(FText::FromString(TEXT("Operate")));
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case EInteractionType::Misc:
		KeypressText->SetText(FText::FromString(TEXT("Interact")));
		InteractionProgressBar->SetVisibility(ESlateVisibility::Collapsed);
		break;
	default:;
	}
	ActionText->SetText(FText::FromString("Action"));
	NameText->SetText(InteractableData->InteractableActorName);
}

float USPInteractionMenuWidget::UpdateInteractionProgress()
{
	return 0.0f;
}
