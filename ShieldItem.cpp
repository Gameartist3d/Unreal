#include "ShieldItem.h"
#include "SPCharacter.h"


UShieldItem::UShieldItem()
{
	ItemDisplayName = FText::FromString(TEXT("Shield"));
	UseActionText = FText::FromString(TEXT("Equip"));
	isShield = true;
}

void UShieldItem::Use(ASPCharacter* Character)
{
	Character->PlayuurInventoryComponent->Shield = this;
}
