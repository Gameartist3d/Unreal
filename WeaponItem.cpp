#include "WeaponItem.h"
#include "SPCharacter.h"


UWeaponItem::UWeaponItem() {

	ItemDisplayName = FText::FromString(TEXT("Weapon"));
	UseActionText = FText::FromString(TEXT("Equip"));
	isWeapon = true;
}

void UWeaponItem::Use(ASPCharacter* Character)
{
	Character->PlayuurInventoryComponent->NewWeapon = this;
}
