//3DNomad LLC


#include "WeaponItem.h"
#include "DefaultCharacter.h"

UWeaponItem::UWeaponItem()
{
	ItemTextData.ItemName = FText::FromString(TEXT("Weapon Item"));
	ItemTextData.ItemDescription = FText::FromString(TEXT("A weapon item."));
	ItemCategory = EItemCategory::Weapon;
	WeaponCategory = EWeaponCategory::Handgun;
	ItemSlots.Add(EItemSlots::MainHand);
}

void UWeaponItem::ApplyDamageTypes(FHitResult HitResult)
{
	AActor* HitActor = HitResult.GetActor();
	if (HitActor && HitActor->GetClass()->ImplementsInterface(UDamageInterface::StaticClass()))
	{
		if (IDamageInterface* HitActorInterface = Cast<IDamageInterface>(HitActor))
		{
			HitActorInterface->ApplyDamages(WeaponDamageTypes, HitResult.BoneName);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Actor does not implement damage interface"));
	}
	
}

void UWeaponItem::ApplyPhysicsForce(FHitResult hitresult)
{
	const FVector ForwardVector = hitresult.GetActor()->GetActorForwardVector();
	const FName HitBone = hitresult.BoneName;
	//Apply physics force to the hit actor bone
	UPrimitiveComponent* HitComponent = hitresult.GetComponent();
	if (HitComponent && HitComponent->IsSimulatingPhysics(HitBone))
	{
		const FVector ImpulseDirection = ForwardVector * PhysicsForce;
		HitComponent->AddForceAtLocation(ImpulseDirection, hitresult.Location, HitBone);
	}
}

float UWeaponItem::CalculateTotalDamage()
{
	float TotalDamage = 0.f;
	for (const auto& Elem : WeaponDamageTypes)
	{
		TotalDamage += Elem.Value;
	}
	return TotalDamage;
}
