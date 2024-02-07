#include "StatsComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	PlayuurLevel = 1;
	PlayuurLvlExp = 0.0f;
	Stamina.MaxStamina = 50;
	Stamina.CurStamina = 50;
	Sanity.MaxSanity = 50;
	Sanity.CurSanity = 50;
	
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

void UStatsComponent::DamageToBodyHealth(FSPDamageType damage, ESPHealthVarNames bodypart)
{
	for (FHealthVariables& body : BodyHealth)
	{
		if (body.HealthVariableName == bodypart)
		{
			body.CurHealth -= damage.DamageAmount;
			body.DamHealth += damage.DamageAmount;
		}
	}

}

void UStatsComponent::AddPlayuurlvlExp(float exptoadd)
{
	PlayuurLvlExp += exptoadd;
	CheckPlayuurlvlup();
}

void UStatsComponent::CheckPlayuurlvlup()
{
	const float ExperiencetoLvl = 50.0f * PlayuurLevel;
	if (PlayuurLvlExp >= ExperiencetoLvl)
	{
		PlayuurLevel++;
		PlayuurLvlExp = 0.0f;
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
		attribute.AttributeExp = 0.0f;
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
		discipline.DisciplineExp = 0.0f;
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
	const float ExperienceToLvl = 100.0f * Skill.SkillLvl;
	if (Skill.SkillExp >= ExperienceToLvl)
	{
		Skill.SkillLvl++;
		Skill.SkillExp = 0.0f;
	}

}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
