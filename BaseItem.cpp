//3DNomad LLC
/*DEPRECATED!!!!!!!!!!!*/

#include "BaseItem.h"

UBaseItem::UBaseItem()
{
	UseActionText = FText::FromString(TEXT("Use"));
	ItemDisplayName = FText::FromString(TEXT("Item"));
	ItemType = ESPItemType::Program;
	ItemRarity = ESPItemRarity::Common;
	ItemDescription = FText::FromString(TEXT("Base Item"));
	ItemWeight = 1.0f;
}

