//3DNomad LLC

#include "ArmorItem.h"
#include "SPCharacter.h"

AArmorItem::AArmorItem()
{
	ItemDisplayName = FText::FromString(TEXT("Armor"));
	ItemType = ESPItemType::Armor;
	ItemSlots.Add(ESPEquipmentSlot::Armor);
	InteractionComponent->InteractionTypes.Add(EInteractionTypes::Pickup);
	InteractionComponent->InteractionTypes.Add(EInteractionTypes::Equip);
	InteractionComponent->InteractionTypes.Add(EInteractionTypes::Examine);
	InteractionComponent->InteractionTypes.Add(EInteractionTypes::Compare);
}

void AArmorItem::Use(ASPCharacter* Character)
{
	
}
