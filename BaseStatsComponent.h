//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FBodyPart.h"
#include "BaseStatsComponent.generated.h"

//For Updating the UI, Related Functions
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatsUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStaminaUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSanityUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMagickaUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBodyPartUpdated, EBodyPartName, BodyPart);

USTRUCT(BlueprintType)
struct FStamina
{
	GENERATED_BODY()

	//Max Stamina by stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxStamina= 1.0f;

	//Max Stamina with modifiers applied
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float MaxModifiedStamina= 1.0f;

	//Current Stamina
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float CurStamina = 1.0f;

	//Base Stamina Regen Rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
	float BaseStaminaRegen = 1.0f;

	//Current Stamina Regen Rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float CurStaminaRegen = 1.0f;
	
};

USTRUCT(BlueprintType)
struct FMagicka
{
	GENERATED_BODY()

	//Max amount of magicka by stats
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magicka")
	float MaxMagicka;

	//Max amount of magicka with modifiers
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magicka")
	float MaxModifiedMagicka;

	//Current amount of magicka
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magicka")
	float CurMagicka;

	//Amount of Magicka that has slowed regeneration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float MagickaFatigue;

	//Speed for channeling spells
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float ChannelSpeed;

	//Number of spells character is able to queue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	int32 SpellStackAmount;

	//Damaged Magicka
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float DamMagicka;

	//Magic to Recover
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float RecMagicka;

	//Base Magicka Regen Rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magicka")
	float BaseMagickaRegenRate;

	//Current Magicka Regen Rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float CurMagickaRegenRate;

	//Channeling Strength
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float ChannelingStrength;

	//Channeling PoolSize
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Magicka")
	float ChannelingPoolSize;
};

USTRUCT(BlueprintType)
struct FSanity
{
	GENERATED_BODY()

	//Max Sanity with stats
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sanity")
	float MaxSanity = 1.0f;

	//Max Sanity with modifiers (this is the amount CurSanity tries to match)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
	float MaxModifiedSanity = 1.0f;

	//Current Sanity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
	float CurSanity = 1.0f;

	//Base Sanity Regen Rate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sanity")
	float BaseRegenSanity = 1.0f;

	//Current Sanity Regen Rate (variable to use in regeneration for sanity)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sanity")
	float CurRegenSanity = 1.0f;
	
};

USTRUCT(BlueprintType)
struct FSPClass
{
	GENERATED_BODY()
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPV1_API UBaseStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseStatsComponent();
	/*Variables*/
	//character's name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FText CharacterName = FText::FromString(TEXT("Z"));

	//character's level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 CharacterLevel = 0;

	//current Character level experience
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CharacterLvlExp = 0.0f;

	//TArray containing all the body parts with health variables
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Stats")
	TArray<FBodyPart> Body;

	//Weight Limit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float WeightLimit = 0.0f;

	//Current Weight
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CurrentWeight = 0.0f;

	//float for Aggro Amount
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AggroAmount = 0.0f;

	/*Delegates*/

	//Delegate for stats update
	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatsUpdated OnStatsUpdated;

	//Delegate for body part update
	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnBodyPartUpdated OnBodyPartUpdated;

	//Delegate for Stamina stats update
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnStaminaUpdated OnStaminaUpdated;

	//Delegate for sanity stats update
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnSanityUpdated OnSanityUpdated;

	//Delegate for magicka stats update
	UPROPERTY(BlueprintAssignable, Category = "Attributes")
	FOnMagickaUpdated OnMagickaUpdated;

	/*Functions*/

	//function to check if the body part status has changed
	UFUNCTION(BlueprintCallable, Category = "Health")
	void CheckBodyPartStatus(FBodyPart BodyPart);

	//getter functions
	UFUNCTION(Category = "Class")
	FORCEINLINE ELlinachgenName GetLlinachgen() const { return Llinachgen; };

	UFUNCTION(Category = "Stats")
	FORCEINLINE float GetKnockbackThreshold() const { return KnockbackThreshold; };
	
	//Sanity Variables
	UFUNCTION(Category = "Sanity")
	FORCEINLINE float GetCurSanity() const { return Sanity.CurSanity; };
	UFUNCTION(Category = "Sanity")
	FORCEINLINE float GetMaxSanity() const { return Sanity.MaxSanity; };
	UFUNCTION(Category = "Sanity")
	FORCEINLINE float GetMaxModifiedSanity() const { return Sanity.MaxModifiedSanity; };
	UFUNCTION(Category = "Sanity")
	FORCEINLINE float GetBaseRegenSanity() const { return Sanity.BaseRegenSanity; };
	UFUNCTION(Category = "Sanity")
	FORCEINLINE float GetCurRegenSanity() const { return Sanity.CurRegenSanity; };

	//Stamina Variables
	UFUNCTION(Category = "Stamina")
	FORCEINLINE float GetCurStamina() const { return Stamina.CurStamina; };
	UFUNCTION(Category = "Stamina")
	FORCEINLINE float GetMaxStamina() const { return Stamina.MaxStamina; };
	UFUNCTION(Category = "Stamina")
	FORCEINLINE float GetMaxModifiedStamina() const { return Stamina.MaxModifiedStamina; };
	UFUNCTION(Category = "Stamina")
	FORCEINLINE float GetBaseRegenStamina() const { return Stamina.BaseStaminaRegen; };
	UFUNCTION(Category = "Stamina")
	FORCEINLINE float GetCurRegenStamina() const { return Stamina.CurStaminaRegen; };

	//Magicka Variables
	UFUNCTION(Category = "Magicka")
	FORCEINLINE float GetCurMagicka() const { return Magicka.CurMagicka; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE float GetMaxMagicka() const { return Magicka.MaxMagicka; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE float GetMaxModifiedMagicka() const { return Magicka.MaxModifiedMagicka; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE float GetBaseRegenMagicka() const { return Magicka.BaseMagickaRegenRate; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE float GetCurRegenMagicka() const { return Magicka.CurMagickaRegenRate; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE float GetChannelSpeed() const { return Magicka.ChannelSpeed; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE float GetChannelStrength() const { return Magicka.ChannelingStrength; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE float GetMagickaFatigue() const { return Magicka.MagickaFatigue; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE float GetDamMagicka() const { return Magicka.DamMagicka; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE float GetRecMagicka() const { return Magicka.RecMagicka; };

	//setter functions
	UFUNCTION(Category = "Class")
	FORCEINLINE void SetLlinachgen(const ELlinachgenName NewLlinachgen) {Llinachgen = NewLlinachgen; };

	UFUNCTION(Category = "Stats")
	FORCEINLINE void SetKnockbackThreshold(const float NewKnockbackThreshold) {KnockbackThreshold = NewKnockbackThreshold; };
	
	//Sanity Variables
	UFUNCTION(Category = "Sanity")
	FORCEINLINE void SetCurSanity(const float NewCurSanity) {Sanity.CurSanity = NewCurSanity; };
	UFUNCTION(Category = "Sanity")
	FORCEINLINE void SetMaxSanity(const float NewMaxSanity) {Sanity.MaxSanity = NewMaxSanity; };
	UFUNCTION(Category = "Sanity")
	FORCEINLINE void SetMaxModifiedSanity(const float NewMaxModifiedSanity) {Sanity.MaxModifiedSanity = NewMaxModifiedSanity; };
	UFUNCTION(Category = "Sanity")
	FORCEINLINE void SetBaseRegenSanity(const float NewBaseRegenSanity) {Sanity.BaseRegenSanity = NewBaseRegenSanity; };
	UFUNCTION(Category = "Sanity")
	FORCEINLINE void SetCurRegenSanity(const float NewCurRegenSanity) {Sanity.CurRegenSanity = NewCurRegenSanity; };

	//Stamina Variables
	UFUNCTION(Category = "Stamina")
	FORCEINLINE void SetCurStamina(const float NewCurStamina) {Stamina.CurStamina = NewCurStamina; };
	UFUNCTION(Category = "Stamina")
	FORCEINLINE void SetMaxStamina(const float NewMaxStamina) {Stamina.MaxStamina = NewMaxStamina; };
	UFUNCTION(Category = "Stamina")
	FORCEINLINE void SetMaxModifiedStamina(const float NewMaxModifiedStamina) {Stamina.CurStamina = NewMaxModifiedStamina; };
	UFUNCTION(Category = "Stamina")
	FORCEINLINE void SetBaseRegenStamina(const float NewBaseRegenStamina) {Stamina.CurStamina = NewBaseRegenStamina; };
	UFUNCTION(Category = "Stamina")
	FORCEINLINE void SetCurRegenStamina(const float NewCurRegenStamina) {Stamina.CurStamina = NewCurRegenStamina; };

	//Magicka Variables
	UFUNCTION(Category = "Magicka")
	FORCEINLINE void SetCurMagicka(const float NewCurMagicka) {Magicka.CurMagicka = NewCurMagicka; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE void SetMaxMagicka(const float NewMaxMagicka) {Magicka.CurMagicka = NewMaxMagicka; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE void SetMaxModifiedMagicka(const float NewMaxModifiedMagicka) {Magicka.CurMagicka = NewMaxModifiedMagicka; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE void SetBaseRegenMagicka(const float NewBaseRegenMagicka) {Magicka.CurMagicka = NewBaseRegenMagicka; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE void SetCurRegenMagicka(const float NewCurRegenMagicka) {Magicka.CurMagicka = NewCurRegenMagicka; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE void SetChannelSpeed(const float NewChannelSpeed) {Magicka.ChannelSpeed = NewChannelSpeed; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE void SetChannelStrength(const float NewChannelStrength) {Magicka.CurMagicka = NewChannelStrength; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE void SetMagickaFatigue(const float NewMagickaFatigue) {Magicka.CurMagicka = NewMagickaFatigue; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE void SetDamMagicka(const float NewDamMagicka) {Magicka.CurMagicka = NewDamMagicka; };
	UFUNCTION(Category = "Magicka")
	FORCEINLINE void SetRecMagicka(const float NewRecMagicka) {Magicka.CurMagicka = NewRecMagicka; };
	
	/*Overrides*/

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	/*Variables*/
	//The selected class for the character, representing their general traits
	UPROPERTY(VisibleAnywhere, Category = "Class")
	ELlinachgenName Llinachgen;

	//Struct containing Stamina data
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	FStamina Stamina;

	//Struct containing Magicka data
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	FMagicka Magicka;

	//Struct containing Sanity data
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	FSanity Sanity;

	//float to determine knockback threshold
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float KnockbackThreshold;
	
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
