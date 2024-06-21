//3DNomad LLC

#include "StatsComponent.h"
#include "SPCharacter.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	TArray<FString> headbonenamez = { "head", "neck_02"};
	TMap<ESPDamageType, float> defaultresistances;
	TArray<FString> torsobonenamez = { "pelvis", "spine_01", "spine_02", "spine_03", "spine_04", "spine_05", "clavicle_l", "clavicle_r", "clavicle_pec_l", "clavicle_pec_r", "clavicle_out_l", "clavicle_scap_l", "clavicle_out_r", "clavicle_scap_r", "neck_01"};
	TArray<FString> larmbonenamez = { "upperarm_l", "lowerarm_l", "hand_l", "index_metacarpal_l", "middle_metacarpal_l", "pinky_metacarpal_l", "ring_metacarpal_l", "thumb_01_l"};
	TArray<FString> rarmbonenamez = { "upperarm_r", "lowerarm_r", "hand_r", "index_metacarpal_r", "middle_metacarpal_r", "pinky_metacarpal_r", "ring_metacarpal_r", "thumb_01_r" };
	TArray<FString> llegbonenamez = { "thigh_l", "calf_l", "foot_l", "ankle_bck_l", "ankle_fwd_l", "ball_l", "calf_twist_01_l", "calf_twist_02_l", "thigh_twist_01_l", "thigh_02_l"};
	TArray<FString> rlegbonenamez = { "thigh_r", "calf_r", "foot_r", "ankle_bck_r", "ankle_fwd_r", "ball_r", "calf_twist_01_r", "calf_twist_02_r", "thigh_twist_01_r", "thigh_02_r" };

	CharacterLevel = 1;
	CharacterName = FText::FromString("Z");
	CharacterLvlExp = 0.0f;
	Stamina.MaxStamina = 50;
	Stamina.CurStamina = 50;
	Sanity.MaxSanity = 50;
	Sanity.CurSanity = 50;
	Attributes.Add(FSPAttribute(EAttributeName::Physical, 1, 0.0f, nullptr));
	Attributes.Add(FSPAttribute(EAttributeName::Mental, 1, 0.0f, nullptr));
	Disciplines.Add(FDiscipline(ESPDisciplineNames::Strength, nullptr, 1, 0.0f, EAttributeName::Physical));
	Disciplines.Add(FDiscipline(ESPDisciplineNames::Endurance, nullptr, 1, 0.0f, EAttributeName::Physical));
	Disciplines.Add(FDiscipline(ESPDisciplineNames::Reflex, nullptr, 1, 0.0f, EAttributeName::Physical));
	Disciplines.Add(FDiscipline(ESPDisciplineNames::Flexibility, nullptr, 1, 0.0f, EAttributeName::Physical));
	Disciplines.Add(FDiscipline(ESPDisciplineNames::Spiritual, nullptr, 1, 0.0f, EAttributeName::Mental));
	Disciplines.Add(FDiscipline(ESPDisciplineNames::Social, nullptr, 1, 0.0f, EAttributeName::Mental));
	Disciplines.Add(FDiscipline(ESPDisciplineNames::Mechanical, nullptr, 1, 0.0f, EAttributeName::Mental));
	Disciplines.Add(FDiscipline(ESPDisciplineNames::Technical, nullptr, 1, 0.0f, EAttributeName::Mental));
	Skills.Add(FSkill(ESPSkillNames::Alchemy, nullptr, 1, 0.0f, ESPDisciplineNames::Technical, ESPDisciplineNames::Spiritual));
	Skills.Add(FSkill(ESPSkillNames::Balance, nullptr, 1, 0.0f, ESPDisciplineNames::Strength, ESPDisciplineNames::Endurance));
	Skills.Add(FSkill(ESPSkillNames::Bartering, nullptr, 1, 0.0f, ESPDisciplineNames::Social, ESPDisciplineNames::Technical));
	Skills.Add(FSkill(ESPSkillNames::Channeling, nullptr, 1, 0.0f, ESPDisciplineNames::Spiritual, ESPDisciplineNames::Endurance));
	Skills.Add(FSkill(ESPSkillNames::Climbing, nullptr, 1, 0.0f, ESPDisciplineNames::Strength, ESPDisciplineNames::Endurance));
	Skills.Add(FSkill(ESPSkillNames::Conjuration, nullptr, 1, 0.0f, ESPDisciplineNames::Spiritual, ESPDisciplineNames::Social));
	Skills.Add(FSkill(ESPSkillNames::Dodging, nullptr, 1, 0.0f, ESPDisciplineNames::Reflex, ESPDisciplineNames::Flexibility));
	Skills.Add(FSkill(ESPSkillNames::Hacking, nullptr, 1, 0.0f, ESPDisciplineNames::Technical, ESPDisciplineNames::Social));
	Skills.Add(FSkill(ESPSkillNames::Invention, nullptr, 1, 0.0f, ESPDisciplineNames::Technical, ESPDisciplineNames::Spiritual));
	Skills.Add(FSkill(ESPSkillNames::Investigation, nullptr, 1, 0.0f, ESPDisciplineNames::Technical, ESPDisciplineNames::Social));
	Skills.Add(FSkill(ESPSkillNames::Manipulation, nullptr, 1, 0.0f, ESPDisciplineNames::Social, ESPDisciplineNames::Spiritual));
	Skills.Add(FSkill(ESPSkillNames::Manufactor, nullptr, 1, 0.0f, ESPDisciplineNames::Mechanical, ESPDisciplineNames::Technical));
	Skills.Add(FSkill(ESPSkillNames::MartialCombat, nullptr, 1, 0.0f, ESPDisciplineNames::Strength, ESPDisciplineNames::Spiritual));
	Skills.Add(FSkill(ESPSkillNames::Medical, nullptr, 1, 0.0f, ESPDisciplineNames::Technical, ESPDisciplineNames::Social));
	Skills.Add(FSkill(ESPSkillNames::OneHandMartialWeapon, nullptr, 1, 0.0f, ESPDisciplineNames::Strength, ESPDisciplineNames::Reflex));
	Skills.Add(FSkill(ESPSkillNames::OneHandProjectileWeapon, nullptr, 1, 0.0f, ESPDisciplineNames::Reflex, ESPDisciplineNames::Mechanical));
	Skills.Add(FSkill(ESPSkillNames::Piloting, nullptr, 1, 0.0f, ESPDisciplineNames::Technical, ESPDisciplineNames::Mechanical));
	Skills.Add(FSkill(ESPSkillNames::Sprinting, nullptr, 1, 0.0f, ESPDisciplineNames::Reflex, ESPDisciplineNames::Endurance));
	Skills.Add(FSkill(ESPSkillNames::Stealth, nullptr, 1, 0.0f, ESPDisciplineNames::Flexibility, ESPDisciplineNames::Mechanical));
	Skills.Add(FSkill(ESPSkillNames::Swimming, nullptr, 1, 0.0f, ESPDisciplineNames::Strength, ESPDisciplineNames::Endurance));
	Skills.Add(FSkill(ESPSkillNames::Throwing, nullptr, 1, 0.0f, ESPDisciplineNames::Reflex, ESPDisciplineNames::Mechanical));
	Skills.Add(FSkill(ESPSkillNames::TwoHandMartialWeapon, nullptr, 1, 0.0f, ESPDisciplineNames::Strength, ESPDisciplineNames::Reflex));
	Skills.Add(FSkill(ESPSkillNames::TwoHandProjectileWeapon, nullptr, 1, 0.0f, ESPDisciplineNames::Mechanical, ESPDisciplineNames::Technical));
	Skills.Add(FSkill(ESPSkillNames::Vaulting, nullptr, 1, 0.0f, ESPDisciplineNames::Flexibility, ESPDisciplineNames::Reflex));
	BodyHealth.Add(FHealthVariables(ESPHealthVarNames::Head, nullptr, false, false, 50.0f, 50.0f, 0.0f, EHeatLevel::Normal, 0.0f, EColdLevel::Normal, 0.0f, 0.0f, EBleedLevel::None, 0.0f, ECrushLevel::None, 0.0f, EShockLevel::None, 0.0f, EPoisonLevel::None, 0.0f, EDemonicCorruptionLevel::None, 0.0f, EDamageLevel::None, defaultresistances, headbonenamez));
	BodyHealth.Add(FHealthVariables(ESPHealthVarNames::Torso, nullptr, false, false, 50.0f, 50.0f, 0.0f, EHeatLevel::Normal, 0.0f, EColdLevel::Normal, 0.0f, 0.0f, EBleedLevel::None, 0.0f, ECrushLevel::None, 0.0f, EShockLevel::None, 0.0f, EPoisonLevel::None, 0.0f, EDemonicCorruptionLevel::None, 0.0f, EDamageLevel::None, defaultresistances, torsobonenamez));
	BodyHealth.Add(FHealthVariables(ESPHealthVarNames::Arm, nullptr, false, true, 50.0f, 50.0f, 0.0f, EHeatLevel::Normal, 0.0f, EColdLevel::Normal, 0.0f, 0.0f, EBleedLevel::None, 0.0f, ECrushLevel::None, 0.0f, EShockLevel::None, 0.0f, EPoisonLevel::None, 0.0f, EDemonicCorruptionLevel::None, 0.0f, EDamageLevel::None, defaultresistances, rarmbonenamez));
	BodyHealth.Add(FHealthVariables(ESPHealthVarNames::Arm, nullptr, true, false, 50.0f, 50.0f, 0.0f, EHeatLevel::Normal, 0.0f, EColdLevel::Normal, 0.0f, 0.0f, EBleedLevel::None, 0.0f, ECrushLevel::None, 0.0f, EShockLevel::None, 0.0f, EPoisonLevel::None, 0.0f, EDemonicCorruptionLevel::None, 0.0f, EDamageLevel::None, defaultresistances, larmbonenamez));
	BodyHealth.Add(FHealthVariables(ESPHealthVarNames::Leg, nullptr, false, true, 50.0f, 50.0f, 0.0f, EHeatLevel::Normal, 0.0f, EColdLevel::Normal, 0.0f, 0.0f, EBleedLevel::None, 0.0f, ECrushLevel::None, 0.0f, EShockLevel::None, 0.0f, EPoisonLevel::None, 0.0f, EDemonicCorruptionLevel::None, 0.0f, EDamageLevel::None, defaultresistances, rlegbonenamez));
	BodyHealth.Add(FHealthVariables(ESPHealthVarNames::Leg, nullptr, true, false, 50.0f, 50.0f, 0.0f, EHeatLevel::Normal, 0.0f, EColdLevel::Normal, 0.0f, 0.0f, EBleedLevel::None, 0.0f, ECrushLevel::None, 0.0f, EShockLevel::None, 0.0f, EPoisonLevel::None, 0.0f, EDemonicCorruptionLevel::None, 0.0f, EDamageLevel::None, defaultresistances, llegbonenamez));
}

FSPAttribute* UStatsComponent::FindAttributeByName(EAttributeName Attributename)
{
	for (FSPAttribute& Attribute : Attributes)
	{
		if (Attribute.AttributeName == Attributename)
		{
			return &Attribute;
		}
	}

	return nullptr;
}

FDiscipline* UStatsComponent::FindDisciplineByName(ESPDisciplineNames Disciplinename)
{
	for (FDiscipline& discipline : Disciplines)
	{
		if (discipline.DisciplineName == Disciplinename)
		{
			return &discipline;
		}
	}

	return nullptr;
}

FSkill* UStatsComponent::FindSkillByName(ESPSkillNames Skillname)
{
	for (FSkill& Skill : Skills)
	{
		if (Skill.SkillName == Skillname)
		{
			return &Skill;
		}
	}

	return nullptr;
}

int32 UStatsComponent::GetAttributelvl(EAttributeName Attributename)
{
	for (FSPAttribute& Attribute : Attributes)
	{
		if (Attribute.AttributeName == Attributename)
		{
			return Attribute.AttributeLvl;
		}
	}
	return 0;
}

void UStatsComponent::CheckHealthVarStatus(FHealthVariables healthvar)
{
	if (healthvar.CurHealth < healthvar.MaxHealth) {
		if (healthvar.CurHealth <= (healthvar.MaxHealth * .2)) {
			healthvar.DamageLevel = EDamageLevel::Light;
		}
		else if (healthvar.CurHealth <= (healthvar.MaxHealth * .4)) {
			healthvar.DamageLevel = EDamageLevel::Medium;
		}
		else if (healthvar.CurHealth <= (healthvar.MaxHealth * .6)) {
			healthvar.DamageLevel = EDamageLevel::Heavy;
		}
		else if (healthvar.CurHealth <= (healthvar.MaxHealth * .8)) {
			healthvar.DamageLevel = EDamageLevel::Severe;
		}
		else if (healthvar.CurHealth < healthvar.MaxHealth) {
			healthvar.DamageLevel = EDamageLevel::Critical;
		}
		else {
			healthvar.DamageLevel = EDamageLevel::Destroyed;
			if (healthvar.HealthVariableName == ESPHealthVarNames::Head || healthvar.HealthVariableName == ESPHealthVarNames::Torso) {
				ASPCharacter* Playuur = Cast<ASPCharacter>(GetOwner());
				if (Playuur) {
					Playuur->Death();
				}
			}
		}
	}
	else {
		healthvar.DamageLevel = EDamageLevel::None;
	}
	if (healthvar.BleedAmount > 0) {
		if (healthvar.BleedAmount <= (healthvar.MaxHealth * .3)) {
			healthvar.BleedLevel = EBleedLevel::Light;
		}
		else if (healthvar.BleedAmount <= (healthvar.MaxHealth * .6)) {
			healthvar.BleedLevel = EBleedLevel::Medium;
		}
		else {
			healthvar.BleedLevel = EBleedLevel::Heavy;
		}
	}
	else {
		healthvar.BleedLevel = EBleedLevel::None;
	}
	if (healthvar.CrushAmount > 0) {
		if (healthvar.CrushAmount <= (healthvar.MaxHealth * .3)) {
			healthvar.CrushLevel = ECrushLevel::Bruised;
		}
		else if (healthvar.CrushAmount < healthvar.MaxHealth) {
			healthvar.CrushLevel = ECrushLevel::Strained;
		}
		else {
			healthvar.CrushLevel = ECrushLevel::Broken;
		}
	}
	else {
		healthvar.CrushLevel = ECrushLevel::None;
	}
	if (healthvar.PoisHealth > 0) {
		if (healthvar.PoisHealth <= (healthvar.MaxHealth * .3)) {
			healthvar.PoisonLevel = EPoisonLevel::Light;
		}
		else if (healthvar.PoisHealth <= (healthvar.MaxHealth * .6)) {
			healthvar.PoisonLevel = EPoisonLevel::Infected;
		}
		else {
			healthvar.PoisonLevel = EPoisonLevel::Toxic;
		}
	}
	else {
		healthvar.PoisonLevel = EPoisonLevel::None;
	}
	if (healthvar.ShockAmount > 0) {
		if (healthvar.ShockAmount <= (healthvar.MaxHealth * .3)) {
			healthvar.ShockLevel = EShockLevel::Light;
		}
		else if (healthvar.ShockAmount <= (healthvar.MaxHealth * .6)) {
			healthvar.ShockLevel = EShockLevel::Spasms;
		}
		else {
			healthvar.ShockLevel = EShockLevel::Seizure;
		}
	}
	else {
		healthvar.ShockLevel = EShockLevel::None;
	}
	if (healthvar.ColdAmount > 0) {
		if (healthvar.ColdAmount <= (healthvar.MaxHealth * .3)) {
			healthvar.ColdLevel = EColdLevel::Cool;
		}
		else if (healthvar.ColdAmount < (healthvar.MaxHealth)) {
			healthvar.ColdLevel = EColdLevel::Freezing;
		}
		else {
			healthvar.ColdLevel = EColdLevel::Frozen;
		}
	}
	else {
		healthvar.ColdLevel = EColdLevel::Normal;
	}
	if (healthvar.HeatAmount > 0) {
		if (healthvar.HeatAmount <= (healthvar.MaxHealth * .3)) {
			healthvar.HeatLevel = EHeatLevel::Warm;
		}
		else if (healthvar.HeatAmount <= (healthvar.MaxHealth * .9)) {
			healthvar.HeatLevel = EHeatLevel::Hot;
		}
		else {
			healthvar.HeatLevel = EHeatLevel::Burning;
		}
	}
	else {
		healthvar.HeatLevel = EHeatLevel::Normal;
	}
	if (healthvar.DemonicCorruption > 0) {
		if (healthvar.DemonicCorruption <= (healthvar.MaxHealth * .3)) {
			healthvar.DemonicCorruptionLevel = EDemonicCorruptionLevel::Light;
		}
		else if (healthvar.DemonicCorruption < (healthvar.MaxHealth)) {
			healthvar.DemonicCorruptionLevel = EDemonicCorruptionLevel::Conflicted;
		}
		else {
			healthvar.DemonicCorruptionLevel = EDemonicCorruptionLevel::Corrupted;
		}
	}
	else {
		healthvar.DemonicCorruptionLevel = EDemonicCorruptionLevel::None;
	}
	OnBodyHealthUpdated.Broadcast(healthvar.HealthVariableName);
}

int32 UStatsComponent::GetDisciplinelvl(ESPDisciplineNames Disciplinename)
{
	for (FDiscipline& discipline : Disciplines)
	{
		if (discipline.DisciplineName == Disciplinename)
		{
			return discipline.DisciplineLvl;
		}
	}
	return 0;
}

int32 UStatsComponent::GetSkilllvl(ESPSkillNames Skillname)
{
	for (FSkill& Skill : Skills)
	{
		if (Skill.SkillName == Skillname)
		{
			return Skill.SkillLvl;
		}
	}
	return 0;
}

void UStatsComponent::AddCharacterlvlExp(float exptoadd)
{
	CharacterLvlExp += exptoadd;
	CheckCharacterlvlup();
}

void UStatsComponent::CheckCharacterlvlup()
{
	const float ExperiencetoLvl = 50.0f * CharacterLevel;
	if (CharacterLvlExp >= ExperiencetoLvl)
	{
		CharacterLevel++;
		CharacterLvlExp = 0.0f;
	}
}

void UStatsComponent::AddAttributeExp(EAttributeName attributename, float ExptoAdd)
{
	FSPAttribute* attribute = FindAttributeByName(attributename);
	if (attribute)
	{
		attribute->AttributeExp += ExptoAdd;
		CheckAttributelvlUp(*attribute);
	}
}

void UStatsComponent::CheckAttributelvlUp(FSPAttribute& attribute)
{
	const float ExperienceToLvl = 100.0f * attribute.AttributeLvl;
	if (attribute.AttributeExp >= ExperienceToLvl)
	{
		attribute.AttributeLvl++;
		CharacterLvlExp += 50 * attribute.AttributeLvl;
		attribute.AttributeExp = 0.0f;
		OnAttributeUpdated.Broadcast(attribute.AttributeName);
	}
}

void UStatsComponent::AddDisciplineExp(ESPDisciplineNames Disciplinename, float ExptoAdd)
{
	FDiscipline* discipline = FindDisciplineByName(Disciplinename);
	if (discipline)
	{
		discipline->DisciplineExp += ExptoAdd;
		CheckDisciplinelvlUp(*discipline);
	}
}

void UStatsComponent::CheckDisciplinelvlUp(FDiscipline& discipline)
{
	const float ExperienceToLvl = 100.0f * discipline.DisciplineLvl;
	if (discipline.DisciplineExp >= ExperienceToLvl)
	{
		discipline.DisciplineLvl++;
		AddAttributeExp(discipline.ParentAttribute, 25.0f * discipline.DisciplineLvl);
		discipline.DisciplineExp = 0.0f;
		OnDisciplineUpdated.Broadcast(discipline.DisciplineName);
	}
}

void UStatsComponent::AddSkillExp(ESPSkillNames Skillname, float ExptoAdd)
{
	FSkill* Skill = FindSkillByName(Skillname);
	if (Skill)
	{
		Skill->SkillExp += ExptoAdd;
		CheckSkilllvlUp(*Skill);
	}
}

void UStatsComponent::CheckSkilllvlUp(FSkill& Skill)
{
	const float ExperienceToLvl = 20.0f * Skill.SkillLvl;
	if (Skill.SkillExp >= ExperienceToLvl)
	{
		Skill.SkillLvl++;
		AddDisciplineExp(Skill.ParentDiscipline, 15.0f * Skill.SkillLvl);
		AddDisciplineExp(Skill.MinorDiscipline, 5.0f * Skill.SkillLvl);
		Skill.SkillExp = 0.0f;
		OnSkillUpdated.Broadcast(Skill.SkillName);
	}

}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


