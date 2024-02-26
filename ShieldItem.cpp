//3DNomad LLC


#include "ShieldItem.h"
#include "SPCharacter.h"


UShieldItem::UShieldItem()
{
	ItemDisplayName = FText::FromString(TEXT("Shield"));
	UseActionText = FText::FromString(TEXT("Equip"));
	ItemType = ESPItemType::Shield;
}

void UShieldItem::Use(ASPCharacter* Character)
{
	Character->PlayuurInventoryComponent->Shield = this;
}
