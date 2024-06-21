//3DNomad LLC

#include "WeaponItem.h"
#include "SPCharacter.h"


AWeaponItem::AWeaponItem() {

	ItemDisplayName = FText::FromString(TEXT("Weapon"));
	ItemType = ESPItemType::Weapon;
	ItemSlots.Add(ESPEquipmentSlot::RightHand);
	ItemSlots.Add(ESPEquipmentSlot::LeftHand);
	AggroAmount = 0.0f;
	PhysicsForce = 1.0f;
	bIsTwoHanded = false;
	WeaponMesh = nullptr;
	InteractionComponent->InteractionTypes.Add(EInteractionTypes::Pickup);
	InteractionComponent->InteractionTypes.Add(EInteractionTypes::Equip);
	InteractionComponent->InteractionTypes.Add(EInteractionTypes::Examine);
	InteractionComponent->InteractionTypes.Add(EInteractionTypes::Compare);
}

void AWeaponItem::ApplyDamageTypes(FHitResult hitresult)
{
	AActor* HitActor = hitresult.GetActor();
	ASPCharacter* HitCharacter = Cast<ASPCharacter>(HitActor);
	if (HitCharacter)
	{


		//Do something if a character was hit
		FName HitBone = hitresult.BoneName;

		for (FHealthVariables& HealthVar : HitCharacter->PlayuurStatsComponent->BodyHealth)
		{
			if (HealthVar.BoneNames.Contains(HitBone)) {
				float totaldamage = CalculateTotalDamage();
				float residualdamage = totaldamage;

				for (const auto& dampair : WeaponStats.WeaponDamageTypes) {
					ESPDamageType damagetype = dampair.Key;
					float damageamount = dampair.Value;

					if (HealthVar.Resistances.Contains(damagetype)) {
						float resistanceamount = HealthVar.Resistances[damagetype];
						residualdamage -= resistanceamount;
					}
					residualdamage = FMath::Max(0.0f, residualdamage);
					switch (damagetype) {
					case ESPDamageType::Blunt:
						HealthVar.CurHealth -= residualdamage;
						HealthVar.CurHealth = FMath::Clamp(HealthVar.CurHealth, 0.0f, HealthVar.MaxHealth);
						HealthVar.DamHealth += (residualdamage / 4.0f);
						HealthVar.DamHealth = FMath::Clamp(HealthVar.DamHealth, 0.0f, HealthVar.MaxHealth);
						HealthVar.CrushAmount += (residualdamage / 2.0f);
						HealthVar.CrushAmount = FMath::Clamp(HealthVar.CrushAmount, 0.0f, HealthVar.MaxHealth);
						break;
					case ESPDamageType::Slice:
						HealthVar.CurHealth -= residualdamage;
						HealthVar.CurHealth = FMath::Clamp(HealthVar.CurHealth, 0.0f, HealthVar.MaxHealth);
						HealthVar.DamHealth += (residualdamage / 2.0f);
						HealthVar.DamHealth = FMath::Clamp(HealthVar.DamHealth, 0.0f, HealthVar.MaxHealth);
						HealthVar.BleedAmount += (residualdamage / 1.5f);
						HealthVar.BleedAmount = FMath::Clamp(HealthVar.BleedAmount, 0.0f, HealthVar.MaxHealth);
						break;
					case ESPDamageType::Pierce:
						HealthVar.CurHealth -= residualdamage;
						HealthVar.CurHealth = FMath::Clamp(HealthVar.CurHealth, 0.0f, HealthVar.MaxHealth);
						HealthVar.DamHealth += (residualdamage / 3.0f);
						HealthVar.DamHealth = FMath::Clamp(HealthVar.DamHealth, 0.0f, HealthVar.MaxHealth);
						HealthVar.BleedAmount += (residualdamage /2.0f);
						HealthVar.BleedAmount = FMath::Clamp(HealthVar.BleedAmount, 0.0f, HealthVar.MaxHealth);
						break;
					case ESPDamageType::Poison: 
						HealthVar.PoisHealth += residualdamage;
						HealthVar.PoisHealth = FMath::Clamp(HealthVar.PoisHealth, 0.0f, HealthVar.MaxHealth);
						break;
					case ESPDamageType::Fire:
						HealthVar.CurHealth -= residualdamage;
						HealthVar.CurHealth = FMath::Clamp(HealthVar.CurHealth, 0.0f, HealthVar.MaxHealth);
						HealthVar.HeatAmount += residualdamage;
						HealthVar.HeatAmount = FMath::Clamp(HealthVar.HeatAmount, 0.0f, HealthVar.MaxHealth);
						break;
					case ESPDamageType::Ice:
						HealthVar.CurHealth -= residualdamage;
						HealthVar.CurHealth = FMath::Clamp(HealthVar.CurHealth, 0.0f, HealthVar.MaxHealth);
						HealthVar.DamHealth += (residualdamage / 3.0f);
						HealthVar.DamHealth = FMath::Clamp(HealthVar.DamHealth, 0.0f, HealthVar.MaxHealth);
						HealthVar.ColdAmount += residualdamage;
						HealthVar.ColdAmount = FMath::Clamp(HealthVar.ColdAmount, 0.0f, HealthVar.MaxHealth);
						break;
					case ESPDamageType::Shock:
						HealthVar.CurHealth -= residualdamage;
						HealthVar.CurHealth = FMath::Clamp(HealthVar.CurHealth, 0.0f, HealthVar.MaxHealth);
						HealthVar.ShockAmount += residualdamage;
						HealthVar.ShockAmount = FMath::Clamp(HealthVar.ShockAmount, 0.0f, HealthVar.MaxHealth);
						break;
					case ESPDamageType::Sanity:
						HitCharacter->PlayuurStatsComponent->Sanity.CurSanity -= residualdamage;
						HitCharacter->PlayuurStatsComponent->Sanity.CurSanity = FMath::Clamp(HitCharacter->PlayuurStatsComponent->Sanity.CurSanity, 0.0f, HitCharacter->PlayuurStatsComponent->Sanity.MaxSanity);
						break;
					case ESPDamageType::Stamina:
						HitCharacter->PlayuurStatsComponent->Stamina.CurStamina -= residualdamage;
						HitCharacter->PlayuurStatsComponent->Stamina.CurStamina = FMath::Clamp(HitCharacter->PlayuurStatsComponent->Stamina.CurStamina, 0.0f, HitCharacter->PlayuurStatsComponent->Stamina.MaxStamina);
						break;
					case ESPDamageType::Demonic:
						HealthVar.CurHealth -= residualdamage;
						HealthVar.CurHealth = FMath::Clamp(HealthVar.CurHealth, 0.0f, HealthVar.MaxHealth);
						HealthVar.DamHealth += (residualdamage / 2.0f);
						HealthVar.DamHealth = FMath::Clamp(HealthVar.DamHealth, 0.0f, HealthVar.MaxHealth);
						HealthVar.DemonicCorruption += residualdamage;
						HealthVar.DemonicCorruption = FMath::Clamp(HealthVar.DemonicCorruption, 0.0f, HealthVar.MaxHealth);
						break;
					}
				}
				//Call function on hit character to check if dead or status change
				HitCharacter->PlayuurStatsComponent->CheckHealthVarStatus(HealthVar);
				break;
			}

		}
	}
}

void AWeaponItem::ApplyPhysicsForce(FHitResult hitresult, ASPCharacter* Character)
{
	FVector ForwardVector = Character->GetActorForwardVector();
	FName hitbone = hitresult.BoneName;
	//Apply physics force to the hit actor bone
	UPrimitiveComponent* hitcomponent = hitresult.GetComponent();
	if (hitcomponent && hitcomponent->IsSimulatingPhysics(hitbone))
	{
		FVector ImpulseDirection = ForwardVector * PhysicsForce;
		hitcomponent->AddForceAtLocation(ImpulseDirection, hitresult.Location, hitbone);
	}
}

float AWeaponItem::CalculateTotalDamage()
{
	float totaldamage = 0.f;
	for (const auto& Elem : WeaponStats.WeaponDamageTypes)
	{
		totaldamage += Elem.Value;
	}
	return totaldamage;
}

void AWeaponItem::Use(ASPCharacter* Character)
{
	
}


