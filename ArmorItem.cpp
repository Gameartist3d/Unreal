//3DNomad LLC

#include "ArmorItem.h"
#include "SPCharacter.h"

UArmorItem::UArmorItem()
{
	ItemDisplayName = FText::FromString(TEXT("Armor"));
	UseActionText = FText::FromString(TEXT("Equip"));
	ItemType = ESPItemType::Armor;
}

void UArmorItem::Use(ASPCharacter* Character)
{
	Character->PlayuurInventoryComponent->Armor = this;
}
