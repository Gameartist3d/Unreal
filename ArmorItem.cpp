#include "ArmorItem.h"
#include "SPCharacter.h"

UArmorItem::UArmorItem()
{
	ItemDisplayName = FText::FromString(TEXT("Armor"));
	UseActionText = FText::FromString(TEXT("Equip"));
	isArmor = true;
}

void UArmorItem::Use(ASPCharacter* Character)
{
	Character->PlayuurInventoryComponent->Armor = this;
}
