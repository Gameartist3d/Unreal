//3DNomad LLC


#include "InventoryComponent.h"
#include "SPBaseItem.h"
#include "WeaponItem.h"
#include "ArmorItem.h"
#include "ShieldItem.h"
#include "SPCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	InventoryCapacity = 100;
	InventoryLockStrength = 0;
	EquippedItems.Add(ESPEquipmentSlot::LeftHand, nullptr);
	EquippedItems.Add(ESPEquipmentSlot::RightHand, nullptr);
	EquippedItems.Add(ESPEquipmentSlot::Throwable, nullptr);
	EquippedItems.Add(ESPEquipmentSlot::Armor, nullptr);
	EquippedItems.Add(ESPEquipmentSlot::Shield, nullptr);
	EquippedItems.Add(ESPEquipmentSlot::Pet, nullptr);

}
	// Called when the game starts
	void UInventoryComponent::BeginPlay()
	{
		Super::BeginPlay();

		for (auto& Item : DefaultItems) {
			AddItem(Item);
		}

		// ...

	}

	bool UInventoryComponent::AddItem(ASPBaseItem* Item)
	{
		if (InventoryItems.Num() >= InventoryCapacity || !Item) {
			return false;
		}
		Item->OwnerInventory = this;
		Item->World = GetWorld();
		InventoryItems.Add(Item);

		//Update UI
		OnInventoryUpdated.Broadcast();
		return true;
	}

	bool UInventoryComponent::RemoveItem(ASPBaseItem* Item) 
	{
		if (Item) {
			Item->OwnerInventory = nullptr;
			Item->World = nullptr;
			InventoryItems.RemoveSingle(Item);
			OnInventoryUpdated.Broadcast();
			return true;

		}
		return false;
	}

	void UInventoryComponent::EquipSlot(ESPEquipmentSlot SlotToEquip, ASPBaseItem* ItemToEquip)
	{
		if (!EquippedItems.Contains(SlotToEquip) || !ItemToEquip) {
			return;
		}

		if (ItemToEquip->ItemSlots.Contains(SlotToEquip))
		{
			if (EquippedItems.Contains(SlotToEquip))
			{
				UnEquipSlot(SlotToEquip);
			}

			EquippedItems.Add(SlotToEquip, ItemToEquip);

			ApplyItemEffects(ItemToEquip);

			OnSlotUpdated.Broadcast(SlotToEquip);
		}
	}

	void UInventoryComponent::UnEquipSlot(ESPEquipmentSlot SlotToUnEquip)
	{
		if (!EquippedItems.Contains(SlotToUnEquip))
		{
			return;
		}

		if (EquippedItems.Contains(SlotToUnEquip))
		{
			RemoveItemEffects(EquippedItems[SlotToUnEquip]);

			EquippedItems.Remove(SlotToUnEquip);

			OnSlotUpdated.Broadcast(SlotToUnEquip);
		}
	}

	void UInventoryComponent::ApplyItemEffects(ASPBaseItem* ItemtoUse)
	{
		//Apply Weapon effects
		if (ItemtoUse->ItemType == ESPItemType::Weapon) {
			AActor* owna = GetOwner();
			if (!owna) {
				return;
			}
			ASPCharacter* characta = Cast<ASPCharacter>(owna);
			if (!characta) {
				return;
			}
			UStatsComponent* statscomp = characta->FindComponentByClass<UStatsComponent>();
			if (!statscomp) {
				return;
			}
			statscomp->CurrentWeight += ItemtoUse->ItemWeight;

			AWeaponItem* weaponitem = Cast<AWeaponItem>(ItemtoUse);
		}
		//Apply Armor effects
		else if (ItemtoUse->ItemType == ESPItemType::Armor) {
			AActor* owna = GetOwner();
			if (!owna) {
				return;
			}
			ASPCharacter* characta = Cast<ASPCharacter>(owna);
			if (!characta) {
				return;
			}
			UStatsComponent* statscomp = characta->FindComponentByClass<UStatsComponent>();
			if (!statscomp) {
				return;
			}
			statscomp->CurrentWeight += ItemtoUse->ItemWeight;

			AArmorItem* armoritem = Cast<AArmorItem>(ItemtoUse);
			if (!armoritem) {
				return;
			}
			if (armoritem && armoritem->ArmorResistances.Num() > 0) {
				for (ESPHealthVarNames& bodypart : armoritem->AffectedHealthVariables) {
					for (FHealthVariables& affectedpart : statscomp->BodyHealth) {
						if (affectedpart.HealthVariableName == bodypart) {
							for (const TPair<ESPDamageType, float>& Pair : armoritem->ArmorResistances) {
								float& CurrentResistance = affectedpart.Resistances.FindOrAdd(Pair.Key);
								CurrentResistance += Pair.Value;
							}
						}
					}
				}
			}
		}
		//Apply Shield Effects
		else if (ItemtoUse->ItemType == ESPItemType::Shield) {
			AShieldItem* shielditem = Cast<AShieldItem>(ItemtoUse);
			if (!shielditem) {
				return;
			}
			AActor* owna = GetOwner();
			if (!owna) {
				return;
			}
			ASPCharacter* characta = Cast<ASPCharacter>(owna);
			if (!characta) {
				return;
			}
			UStatsComponent* statscomp = characta->FindComponentByClass<UStatsComponent>();
			if (!statscomp) {
				return;
			}
			statscomp->CurrentWeight += ItemtoUse->ItemWeight;

			if (shielditem && shielditem->ShieldResistances.Num() > 0) {
					for (FHealthVariables& bodyparts : statscomp->BodyHealth) {
							for (const TPair<ESPDamageType, float>& Pair : shielditem->ShieldResistances) {
								float& CurrentResistance = bodyparts.Resistances.FindOrAdd(Pair.Key);
								CurrentResistance += Pair.Value;
							}
					}
			}	
		}

		//Apply Consumable Effects
		else if (ItemtoUse->ItemType == ESPItemType::Consumable) {

		}
		//Apply Material Effects
		else if (ItemtoUse->ItemType == ESPItemType::Material) {

		}
		//Apply Pet Effects
		else if (ItemtoUse->ItemType == ESPItemType::Pet) {

		}
		//Apply Key Effects
		else if (ItemtoUse->ItemType == ESPItemType::Key) {

		}
		//Apply Actionable Effects
		else if (ItemtoUse->ItemType == ESPItemType::Actionable) {

		}
		//Apply Prop Effects
		else if (ItemtoUse->ItemType == ESPItemType::Prop) {

		}
		//Apply Mission Effects
		else if (ItemtoUse->ItemType == ESPItemType::Mission) {

		}
		//Apply Program Effects
		else if (ItemtoUse->ItemType == ESPItemType::Program) {

		}
	}

	void UInventoryComponent::RemoveItemEffects(ASPBaseItem* ItemToRemove) {

		//Remove Weapon effects
		if (ItemToRemove->ItemType == ESPItemType::Weapon) {
			AActor* owna = GetOwner();
			if (!owna) {
				return;
			}
			ASPCharacter* characta = Cast<ASPCharacter>(owna);
			if (!characta) {
				return;
			}
			UStatsComponent* statscomp = characta->FindComponentByClass<UStatsComponent>();
			if (!statscomp) {
				return;
			}
			statscomp->CurrentWeight -= ItemToRemove->ItemWeight;
		}
		//Remove Armor effects
		else if (ItemToRemove->ItemType == ESPItemType::Armor) {
			AArmorItem* armoritem = Cast<AArmorItem>(ItemToRemove);
			if (!armoritem) {
				return;
			}
			AActor* owna = GetOwner();
			if (!owna) {
				return;
			}
			ASPCharacter* characta = Cast<ASPCharacter>(owna);
			if (!characta) {
				return;
			}
			UStatsComponent* statscomp = characta->FindComponentByClass<UStatsComponent>();
			if (!statscomp) {
				return;
			}
			statscomp->CurrentWeight -= ItemToRemove->ItemWeight;

			if (armoritem && armoritem->ArmorResistances.Num() > 0) {
				for (ESPHealthVarNames& bodypart : armoritem->AffectedHealthVariables) {
					for (FHealthVariables& affectedpart : statscomp->BodyHealth) {
						if (affectedpart.HealthVariableName == bodypart) {
							for (const TPair<ESPDamageType, float>& Pair : armoritem->ArmorResistances) {
								float& CurrentResistance = affectedpart.Resistances.FindOrAdd(Pair.Key);
								CurrentResistance -= Pair.Value;
							}
						}
					}
				}
			}
		}
		//Remove Shield Effects
		else if (ItemToRemove->ItemType == ESPItemType::Shield) {
			AShieldItem* shielditem = Cast<AShieldItem>(ItemToRemove);
			if (!shielditem) {
				return;
			}
			AActor* owna = GetOwner();
			if (!owna) {
				return;
			}
			ASPCharacter* characta = Cast<ASPCharacter>(owna);
			if (!characta) {
				return;
			}
			UStatsComponent* statscomp = characta->FindComponentByClass<UStatsComponent>();
			if (!statscomp) {
				return;
			}
			statscomp->CurrentWeight -= ItemToRemove->ItemWeight;

			if (shielditem && shielditem->ShieldResistances.Num() > 0) {
				for (FHealthVariables& bodyparts : statscomp->BodyHealth) {
					for (const TPair<ESPDamageType, float>& Pair : shielditem->ShieldResistances) {
						float& CurrentResistance = bodyparts.Resistances.FindOrAdd(Pair.Key);
						CurrentResistance -= Pair.Value;
					}
				}
			}
		}
		//Remove Consumable Effects
		else if (ItemToRemove->ItemType == ESPItemType::Consumable) {

		}
		//Remove Material Effects
		else if (ItemToRemove->ItemType == ESPItemType::Material) {

		}
		//Remove Pet Effects
		else if (ItemToRemove->ItemType == ESPItemType::Pet) {

		}
		//Remove Key Effects
		else if (ItemToRemove->ItemType == ESPItemType::Key) {

		}
		//Remove Actionable Effects
		else if (ItemToRemove->ItemType == ESPItemType::Actionable) {

		}
		//Remove Prop Effects
		else if (ItemToRemove->ItemType == ESPItemType::Prop) {

		}
		//Remove Mission Effects
		else if (ItemToRemove->ItemType == ESPItemType::Mission) {

		}
		//Remove Program Effects
		else if (ItemToRemove->ItemType == ESPItemType::Program) {

		}
	}

	void UInventoryComponent::AddAmmo(ESPAmmoName AmmoToAdd, float amount)
	{
		if (Ammo.Contains(AmmoToAdd)) {
		Ammo[AmmoToAdd] += amount;
		}
		else {
			Ammo.Add(AmmoToAdd, amount);
		}
	}

	void UInventoryComponent::RemoveAmmo(ESPAmmoName AmmoToRemove, float amount)
	{
		if (Ammo.Contains(AmmoToRemove)) {
			Ammo[AmmoToRemove] = FMath::Max(0.f, Ammo[AmmoToRemove] - amount);

			if (Ammo[AmmoToRemove] <= 0) {
				Ammo.Remove(AmmoToRemove);
			}
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Ammo not found"), *UEnum::GetValueAsString(AmmoToRemove));
		 }
	}

	void UInventoryComponent::AddCurrency(ESPCurrency CurrencyToAdd, float amount)
	{
		if(Currencies.Contains(CurrencyToAdd))
		{
			Currencies[CurrencyToAdd] += amount;
		}
		else
		{
			Currencies.Add(CurrencyToAdd, amount);
		}
		
	}

	void UInventoryComponent::RemoveCurrency(ESPCurrency CurrencyToRemove, float amount)
	{
		if (Currencies.Contains(CurrencyToRemove)) {
			Currencies[CurrencyToRemove] = FMath::Max(0.f, Currencies[CurrencyToRemove] - amount);

			if (Currencies[CurrencyToRemove] <= 0) {
				Currencies.Remove(CurrencyToRemove);
			}
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s Currency not found"), *UEnum::GetValueAsString(CurrencyToRemove));
		}
	}

