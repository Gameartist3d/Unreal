#include "HealthItem.h"
#include "SPCharacter.h"


UHealthItem::UHealthItem()
{
	
}

void UHealthItem::Use(ASPCharacter* Character)
{
	if (Character) {
		for (auto& Healthob : Character->PlayuurStatsComponent->BodyHealth)
		{
			if (Healthob.DamHealth > 0.0f) {
				Healthob.DamHealth -= HealthtoRecover;
				if (Healthob.DamHealth < 0.0f) {
					Healthob.DamHealth = 0.0f;
				}
				Healthob.RecHealth += HealthtoRecover;
				if (Healthob.RecHealth > Healthob.MaxHealth) {
					Healthob.RecHealth = Healthob.MaxHealth;
				}
				Character->PlayuurStatsComponent->OnStatsUpdated.Broadcast();
			}
		}
		if (OwnerInventory) {
			OwnerInventory->RemoveItem(this);
		}

	}
}
