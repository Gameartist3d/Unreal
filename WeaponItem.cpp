//3DNomad LLC

#include "WeaponItem.h"
#include "SPCharacter.h"


UWeaponItem::UWeaponItem() {

	ItemDisplayName = FText::FromString(TEXT("Weapon"));
	UseActionText = FText::FromString(TEXT("Equip"));
	ItemType = ESPItemType::Weapon;
}

void UWeaponItem::Use(ASPCharacter* Character)
{
	
}


