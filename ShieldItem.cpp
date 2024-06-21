//3DNomad LLC


#include "ShieldItem.h"
#include "SPCharacter.h"


AShieldItem::AShieldItem()
{
	ItemDisplayName = FText::FromString(TEXT("Shield"));
	ItemType = ESPItemType::Shield;
	ItemSlots.Add(ESPEquipmentSlot::Shield);
	ShieldRegenDelay = 5.0f;
	ShieldRegenRate = 5.0f;
	ShieldStrength = 10.0f;
	ShieldCurrentStrength = 10.0f;
	ShieldHackedAmount = 0.0f;
	ShieldColour = EShieldColour::None;
	InteractionComponent->InteractionTypes.Add(EInteractionTypes::Pickup);
	InteractionComponent->InteractionTypes.Add(EInteractionTypes::Equip);
	InteractionComponent->InteractionTypes.Add(EInteractionTypes::Examine);
	InteractionComponent->InteractionTypes.Add(EInteractionTypes::Compare);
}

void AShieldItem::UpdateShieldBroken()
{
	if (ShieldCurrentStrength <= 0.0f) {
		bShieldBroken = true;
	}
	else {
		bShieldBroken = false;
	}
}

void AShieldItem::Use(ASPCharacter* Character)
{
	
}
