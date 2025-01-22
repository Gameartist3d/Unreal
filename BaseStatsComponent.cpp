//3DNomad LLC

#include "BaseStatsComponent.h"
#include "DefaultCharacter.h"
// Sets default values for this component's properties
UBaseStatsComponent::UBaseStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	TMap<EDamageType, float> defaultresistances;
	TArray<FString> headbonenamez = { "head", "neck_02" };
	TArray<FString> torsobonenamez = { "pelvis", "spine_01", "spine_02", "spine_03", "spine_04", "spine_05", "clavicle_l", "clavicle_r", "clavicle_pec_l", "clavicle_pec_r", "clavicle_out_l", "clavicle_scap_l", "clavicle_out_r", "clavicle_scap_r", "neck_01" };
	TArray<FString> larmbonenamez = { "upperarm_l", "lowerarm_l", "hand_l", "index_metacarpal_l", "middle_metacarpal_l", "pinky_metacarpal_l", "ring_metacarpal_l", "thumb_01_l" };
	TArray<FString> rarmbonenamez = { "upperarm_r", "lowerarm_r", "hand_r", "index_metacarpal_r", "middle_metacarpal_r", "pinky_metacarpal_r", "ring_metacarpal_r", "thumb_01_r" };
	TArray<FString> llegbonenamez = { "thigh_l", "calf_l", "foot_l", "ankle_bck_l", "ankle_fwd_l", "ball_l", "calf_twist_01_l", "calf_twist_02_l", "thigh_twist_01_l", "thigh_02_l" };
	TArray<FString> rlegbonenamez = { "thigh_r", "calf_r", "foot_r", "ankle_bck_r", "ankle_fwd_r", "ball_r", "calf_twist_01_r", "calf_twist_02_r", "thigh_twist_01_r", "thigh_02_r" };
	Body.Add(FBodyPart(EBodyPartName::Head, nullptr, headbonenamez, 50.0f, 50.0f, 0.0f, EDamageLevel::None, 0.0f, 0.0f, EPoisonLevel::None, 0.0f, EBleedLevel::None, 0.0f, EHeatLevel::Normal, 0.0f, EColdLevel::Normal, 0.0f, EShockLevel::None, 0.0f, ECrushLevel::None, 0.0f, EDemonicCorruptionLevel::None, 1.0f, defaultresistances));
	Body.Add(FBodyPart(EBodyPartName::Torso, nullptr, torsobonenamez, 50.0f, 50.0f, 0.0f, EDamageLevel::None, 0.0f, 0.0f, EPoisonLevel::None, 0.0f, EBleedLevel::None, 0.0f, EHeatLevel::Normal, 0.0f, EColdLevel::Normal, 0.0f, EShockLevel::None, 0.0f, ECrushLevel::None, 0.0f, EDemonicCorruptionLevel::None, 1.0f, defaultresistances));
	Body.Add(FBodyPart(EBodyPartName::LeftArm, nullptr, larmbonenamez, 50.0f, 50.0f, 0.0f, EDamageLevel::None, 0.0f, 0.0f, EPoisonLevel::None, 0.0f, EBleedLevel::None, 0.0f, EHeatLevel::Normal, 0.0f, EColdLevel::Normal, 0.0f, EShockLevel::None, 0.0f, ECrushLevel::None, 0.0f, EDemonicCorruptionLevel::None, 1.0f, defaultresistances));
	Body.Add(FBodyPart(EBodyPartName::RightArm, nullptr, rarmbonenamez, 50.0f, 50.0f, 0.0f, EDamageLevel::None, 0.0f, 0.0f, EPoisonLevel::None, 0.0f, EBleedLevel::None, 0.0f, EHeatLevel::Normal, 0.0f, EColdLevel::Normal, 0.0f, EShockLevel::None, 0.0f, ECrushLevel::None, 0.0f, EDemonicCorruptionLevel::None, 1.0f, defaultresistances));
	Body.Add(FBodyPart(EBodyPartName::LeftLeg, nullptr, llegbonenamez, 50.0f, 50.0f, 0.0f, EDamageLevel::None, 0.0f, 0.0f, EPoisonLevel::None, 0.0f, EBleedLevel::None, 0.0f, EHeatLevel::Normal, 0.0f, EColdLevel::Normal, 0.0f, EShockLevel::None, 0.0f, ECrushLevel::None, 0.0f, EDemonicCorruptionLevel::None, 1.0f, defaultresistances));
	Body.Add(FBodyPart(EBodyPartName::RightLeg, nullptr, rlegbonenamez, 50.0f, 50.0f, 0.0f, EDamageLevel::None, 0.0f, 0.0f, EPoisonLevel::None, 0.0f, EBleedLevel::None, 0.0f, EHeatLevel::Normal, 0.0f, EColdLevel::Normal, 0.0f, EShockLevel::None, 0.0f, ECrushLevel::None, 0.0f, EDemonicCorruptionLevel::None, 1.0f, defaultresistances));

	// ...
}


// Called when the game starts
void UBaseStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UBaseStatsComponent::CheckBodyPartStatus(FBodyPart BodyPart)
{
	if (BodyPart.CurHealth < BodyPart.MaxHealth) {
		if (BodyPart.CurHealth <= (BodyPart.MaxHealth * .2)) {
			BodyPart.DamageLevel = EDamageLevel::Light;
		}
		else if (BodyPart.CurHealth <= (BodyPart.MaxHealth * .4)) {
			BodyPart.DamageLevel = EDamageLevel::Medium;
		}
		else if (BodyPart.CurHealth <= (BodyPart.MaxHealth * .6)) {
			BodyPart.DamageLevel = EDamageLevel::Heavy;
		}
		else if (BodyPart.CurHealth <= (BodyPart.MaxHealth * .8)) {
			BodyPart.DamageLevel = EDamageLevel::Severe;
		}
		else if (BodyPart.CurHealth < BodyPart.MaxHealth) {
			BodyPart.DamageLevel = EDamageLevel::Critical;
		}
		else {
			BodyPart.DamageLevel = EDamageLevel::Destroyed;
			if (BodyPart.BodyPartName == EBodyPartName::Head || BodyPart.BodyPartName == EBodyPartName::Torso) {
			}
		}
	}
	else {
		BodyPart.DamageLevel = EDamageLevel::None;
	}
	if (BodyPart.BleedAmount > 0) {
		if (BodyPart.BleedAmount <= (BodyPart.MaxHealth * .3)) {
			BodyPart.BleedLevel = EBleedLevel::Light;
		}
		else if (BodyPart.BleedAmount <= (BodyPart.MaxHealth * .6)) {
			BodyPart.BleedLevel = EBleedLevel::Medium;
		}
		else {
			BodyPart.BleedLevel = EBleedLevel::Heavy;
		}
	}
	else {
		BodyPart.BleedLevel = EBleedLevel::None;
	}
	if (BodyPart.CrushAmount > 0) {
		if (BodyPart.CrushAmount <= (BodyPart.MaxHealth * .3)) {
			BodyPart.CrushLevel = ECrushLevel::Bruised;
		}
		else if (BodyPart.CrushAmount < BodyPart.MaxHealth) {
			BodyPart.CrushLevel = ECrushLevel::Strained;
		}
		else {
			BodyPart.CrushLevel = ECrushLevel::Broken;
		}
	}
	else {
		BodyPart.CrushLevel = ECrushLevel::None;
	}
	if (BodyPart.PoisAmount > 0) {
		if (BodyPart.PoisAmount <= (BodyPart.MaxHealth * .3)) {
			BodyPart.PoisonLevel = EPoisonLevel::Light;
		}
		else if (BodyPart.PoisAmount <= (BodyPart.MaxHealth * .6)) {
			BodyPart.PoisonLevel = EPoisonLevel::Infected;
		}
		else {
			BodyPart.PoisonLevel = EPoisonLevel::Toxic;
		}
	}
	else {
		BodyPart.PoisonLevel = EPoisonLevel::None;
	}
	if (BodyPart.ShockAmount > 0) {
		if (BodyPart.ShockAmount <= (BodyPart.MaxHealth * .3)) {
			BodyPart.ShockLevel = EShockLevel::Light;
		}
		else if (BodyPart.ShockAmount <= (BodyPart.MaxHealth * .6)) {
			BodyPart.ShockLevel = EShockLevel::Spasms;
		}
		else {
			BodyPart.ShockLevel = EShockLevel::Seizure;
		}
	}
	else 
	{
		BodyPart.ShockLevel = EShockLevel::None;
	}
	if (BodyPart.FreezeAmount > 0)
	{
		if (BodyPart.FreezeAmount <= (BodyPart.MaxHealth * .3))
		{
			BodyPart.ColdLevel = EColdLevel::Cool;
		}
		else if (BodyPart.FreezeAmount < (BodyPart.MaxHealth))
		{
			BodyPart.ColdLevel = EColdLevel::Freezing;
		}
		else 
		{
			BodyPart.ColdLevel = EColdLevel::Frozen;
		}
	}
	else 
	{
		BodyPart.ColdLevel = EColdLevel::Normal;
	}
	if (BodyPart.BurnAmount > 0)
	{
		if (BodyPart.BurnAmount <= (BodyPart.MaxHealth * .3))
		{
			BodyPart.HeatLevel = EHeatLevel::Warm;
		}
		else if (BodyPart.BurnAmount <= (BodyPart.MaxHealth * .9))
		{
			BodyPart.HeatLevel = EHeatLevel::Hot;
		}
		else 
		{
			BodyPart.HeatLevel = EHeatLevel::Burning;
		}
	}
	else 
	{
		BodyPart.HeatLevel = EHeatLevel::Normal;
	}
	if (BodyPart.CursedAmount > 0)
	{
		if (BodyPart.CursedAmount <= (BodyPart.MaxHealth * .3))
		{
			BodyPart.DemonicCorruptionLevel = EDemonicCorruptionLevel::Light;
		}
		else if (BodyPart.CursedAmount < (BodyPart.MaxHealth))
		{
			BodyPart.DemonicCorruptionLevel = EDemonicCorruptionLevel::Conflicted;
		}
		else 
		{
			BodyPart.DemonicCorruptionLevel = EDemonicCorruptionLevel::Corrupted;
		}
	}
	else 
	{
		BodyPart.DemonicCorruptionLevel = EDemonicCorruptionLevel::None;
	}
	OnBodyPartUpdated.Broadcast(BodyPart.BodyPartName);
}

// Called every frame
void UBaseStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


