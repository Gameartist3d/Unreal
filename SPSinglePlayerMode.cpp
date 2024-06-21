//3DNomad LLC

#include "SPSinglePlayerMode.h"

void ASPSinglePlayerMode::PawnKilled(APawn* killedpawn)
{
	Super::PawnKilled(killedpawn);

	UE_LOG(LogTemp, Warning, TEXT("Pawn was killed, Ack!"));
}
