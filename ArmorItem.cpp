//3DNomad LLC


#include "ArmorItem.h"

UArmorItem::UArmorItem()
{
	ItemSlots.Add(EItemSlots::Armor);
	ItemCategory = EItemCategory::Armor;
	ItemTextData.ItemDescription = FText::FromString(TEXT("Armor Item"));
	Colour = EArmorColour::Grey;
}

void UArmorItem::Use(APlayerCharacter* Character)
{
	Super::Use(Character);
}
