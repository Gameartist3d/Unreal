#include "BaseItem.h"

UBaseItem::UBaseItem()
{
	UseActionText = FText::FromString(TEXT("Use"));
	ItemDisplayName = FText::FromString(TEXT("Item"));
	ItemDescription = FText::FromString(TEXT("Base Item"));
	ItemWeight = 1.0f;
}
