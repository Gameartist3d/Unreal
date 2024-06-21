//3DNomad LLC


#include "SPBaseItem.h"

// Sets default values
ASPBaseItem::ASPBaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	ItemDisplayName = FText::FromString("Item");
	ItemType = ESPItemType::Consumable;
	ItemRarity = ESPItemRarity::Common;
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
	ItemDescription = FText::FromString("Item Description");
	ItemWeight = 1.0f;
	OwnerInventory = nullptr;
	bIsOwned = false;
}

// Called when the game starts or when spawned
void ASPBaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASPBaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

