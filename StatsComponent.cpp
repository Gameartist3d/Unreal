// Fill out your copyright notice in the Description page of Project Settings.


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
		PlayuurLvlExp += 50 * attribute.AttributeLvl;
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


