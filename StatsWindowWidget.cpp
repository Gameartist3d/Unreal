//3DNomad LLC


#include "StatsWindowWidget.h"
//SP includes
#include "PlayerCharacter.h"
#include "PlayerStatsComponent.h"

void UStatsWindowWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (const APlayerCharacter* OwningPlayer = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		if (UPlayerStatsComponent* OwnerStats = Cast<UPlayerStatsComponent>(OwningPlayer->GetComponentByClass(UPlayerStatsComponent::StaticClass())))
		{
			OwnerStatsComponent = OwnerStats;
		}
	}
}
