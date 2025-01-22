//3DNomad LLC

#include "PlayerHUD.h"
#include "MenusWidget.h"
#include "SPInteractionMenuWidget.h"
#include "SPCrosshairWidget.h"

APlayerHUD::APlayerHUD()
{
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MenusWidgetClass)
	{
		MenusWidget = CreateWidget<UMenusWidget>(GetWorld(), MenusWidgetClass);
		MenusWidget->AddToViewport(2);
		MenusWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (InteractionMenuWidgetClass)
	{
		InteractionMenuWidget = CreateWidget<USPInteractionMenuWidget>(GetWorld(), InteractionMenuWidgetClass);
		InteractionMenuWidget->AddToViewport(1);
		InteractionMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (CrosshairWidgetClass)
	{
		CrosshairWidget = CreateWidget<USPCrosshairWidget>(GetWorld(), CrosshairWidgetClass);
		CrosshairWidget->AddToViewport();
		CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerHUD::DisplayMenu()
{
	if (MenusWidget)
	{
		bIsMenusVisible = true;
		MenusWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerHUD::HideMenu()
{
	if (MenusWidget)
	{
		bIsMenusVisible = false;
		MenusWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerHUD::ToggleMenu()
{
	if(bIsMenusVisible)
	{
		HideMenu();

		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		DisplayMenu();
		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void APlayerHUD::ShowInteractionMenu() const
{
	if (InteractionMenuWidget)
	{
		InteractionMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerHUD::HideInteractionMenu() const
{
	if (InteractionMenuWidget)
	{
		InteractionMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerHUD::UpdateInteractionMenu(const FInteractableData* InteractableData) const
{
	if (InteractionMenuWidget)
	{
		if (InteractionMenuWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionMenuWidget->SetVisibility(ESlateVisibility::Visible);
		}
		InteractionMenuWidget->UpdateInteractionMenu(InteractableData);
	}
}

void APlayerHUD::ShowCrosshair() const
{
	if (CrosshairWidget)
	{
		CrosshairWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APlayerHUD::HideCrosshair() const
{
	if (CrosshairWidget)
	{
		CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void APlayerHUD::UpdateCrosshairTexture(UTexture2D* CrosshairTexture) const
{
	if (CrosshairWidget)
	{
		//CrosshairWidget->set(CrosshairTexture);
	}
}

void APlayerHUD::UpdateCrosshairLocation(const FVector2D& Location)
{
	if (CrosshairWidget)
	{
		CrosshairWidget->SetPositionInViewport(Location, false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("CrosshairWidget is null"));
	}
}


