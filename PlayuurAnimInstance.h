//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayuurAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SP_API UPlayuurAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

protected:

	//float to track Playuur Speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	//float to track Playuur Direction
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveState")
	//Bool To Track when the Playuur has started to fall 
	bool bIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveState")
	//Bool to Track when the Playuur is sprinting
	bool bIsSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveState")
	//Bool to Track when the Playurr is sliding
	bool bIsSliding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveState")
	//Bool to Track when the Playuur is climbing
	bool bIsClimbing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveState")
	//Bool to Track when the Playuur is vaulting
	bool bIsVaulting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveCondition")
	//Bool to Track when the Playuur is reloading
	bool bIsReloading;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveState")
	//Bool to Track when the Playuur is flying
	bool bIsFlying;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveCondition")
	//Bool to Track when the Playuur is on fire
	bool bIsBurning;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveState")
	//Bool to Track when the Playuur is dead
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveModifier")
	//Float to track Playuur fatigue
	float Fatigue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveModifier")
	//Float percentage from stamina  Playuur has left
	float StaminaFatigue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveModifier")
	//Float percentage from magicka  Playuur has left
	float MagickaFatigue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveModifier")
	//Float percentage from heat  Playuur has resisted
	float HeatFatigue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveModifier")
	//Float percentage from cold  Playuur has resisted
	float ColdFatigue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveModifier")
	//float percentage of how much damage Larm has taken
	float LarmDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveModifier")
	//float percentage of how much damage Rarm has taken
	float RarmDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveModifier")
	//float percentage of how much damage Lleg has taken
	float LlegDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveModifier")
	//float percentage of how much damage Rleg has taken
	float RlegDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveModifier")
	//float percentage of how much damage Chest has taken
	float ChestDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MoveModifier")
	//float percentage of how much damage Head has taken
	float HeadDamage;
	
};
