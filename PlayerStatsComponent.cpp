//3DNomad LLC

#include "PlayerStatsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerStatsComponent::UPlayerStatsComponent()
{
	//iniatilize the owner
	OwnerCharacter = Cast<ADefaultCharacter>(GetOwner());

	Attributes.Add(FAttribute(EAttributeName::Mental, 1, nullptr, 0.0f, 0.0f, 0.0f));
	Attributes.Add(FAttribute(EAttributeName::Physical, 1, nullptr, 0.0f, 0.0f, 0.0f));
	Disciplines.Add(FDiscipline(EDisciplineName::Strength, 1, nullptr, 0.0f, 0.0f, 0.0f, EAttributeName::Physical));
	Disciplines.Add(FDiscipline(EDisciplineName::Reflex, 1, nullptr, 0.0f, 0.0f, 0.0f, EAttributeName::Physical));
	Disciplines.Add(FDiscipline(EDisciplineName::Endurance, 1, nullptr, 0.0f, 0.0f, 0.0f, EAttributeName::Physical));
	Disciplines.Add(FDiscipline(EDisciplineName::Flexibility, 1, nullptr, 0.0f, 0.0f, 0.0f, EAttributeName::Physical));
	Disciplines.Add(FDiscipline(EDisciplineName::Spiritual, 1, nullptr, 0.0f, 0.0f, 0.0f, EAttributeName::Mental));
	Disciplines.Add(FDiscipline(EDisciplineName::Technical, 1, nullptr, 0.0f, 0.0f, 0.0f, EAttributeName::Mental));
	Disciplines.Add(FDiscipline(EDisciplineName::Mechanical, 1, nullptr, 0.0f, 0.0f, 0.0f, EAttributeName::Mental));
	Disciplines.Add(FDiscipline(EDisciplineName::Social, 1, nullptr, 0.0f, 0.0f, 0.0f, EAttributeName::Mental));
	Skills.Add(FSkill(ESkillName::Alchemy, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Technical, EDisciplineName::Spiritual));
	Skills.Add(FSkill(ESkillName::Balance, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Flexibility, EDisciplineName::Endurance));
	Skills.Add(FSkill(ESkillName::Bartering, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Social, EDisciplineName::Technical));
	Skills.Add(FSkill(ESkillName::Channeling, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Spiritual, EDisciplineName::Endurance));
	Skills.Add(FSkill(ESkillName::Climbing, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Strength, EDisciplineName::Endurance));
	Skills.Add(FSkill(ESkillName::Conjuration, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Spiritual, EDisciplineName::Social));
	Skills.Add(FSkill(ESkillName::Dodging, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Reflex, EDisciplineName::Flexibility));
	Skills.Add(FSkill(ESkillName::Hacking, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Technical, EDisciplineName::Social));
	Skills.Add(FSkill(ESkillName::Invention, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Technical, EDisciplineName::Spiritual));
	Skills.Add(FSkill(ESkillName::Investigation, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Technical, EDisciplineName::Social));
	Skills.Add(FSkill(ESkillName::Manipulation, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Social, EDisciplineName::Spiritual));
	Skills.Add(FSkill(ESkillName::Manufactor, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Mechanical, EDisciplineName::Technical));
	Skills.Add(FSkill(ESkillName::MartialCombat, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Strength, EDisciplineName::Spiritual));
	Skills.Add(FSkill(ESkillName::Medical, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Technical, EDisciplineName::Social));
	Skills.Add(FSkill(ESkillName::OneHandMartialWeapon, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Strength, EDisciplineName::Reflex));
	Skills.Add(FSkill(ESkillName::OneHandProjectileWeapon, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Reflex, EDisciplineName::Mechanical));
	Skills.Add(FSkill(ESkillName::Piloting, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Technical, EDisciplineName::Mechanical));
	Skills.Add(FSkill(ESkillName::Sprinting, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Reflex, EDisciplineName::Endurance));
	Skills.Add(FSkill(ESkillName::Stealth, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Flexibility, EDisciplineName::Mechanical));
	Skills.Add(FSkill(ESkillName::Swimming, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Strength, EDisciplineName::Endurance));
	Skills.Add(FSkill(ESkillName::Throwing, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Reflex, EDisciplineName::Mechanical));
	Skills.Add(FSkill(ESkillName::TwoHandMartialWeapon, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Strength, EDisciplineName::Reflex));
	Skills.Add(FSkill(ESkillName::TwoHandProjectileWeapon, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Mechanical, EDisciplineName::Technical));
	Skills.Add(FSkill(ESkillName::Vaulting, 1, nullptr, 0.0f, 0.0f, 0.0f, EDisciplineName::Flexibility, EDisciplineName::Reflex));
}

void UPlayerStatsComponent::AddSkillExp(ESkillName Skillname, float ExptoAdd)
{
	FSkill* Skill = FindSkillByName(Skillname);
	if (Skill)
	{
		Skill->SkillExperience += ExptoAdd;
		OnSkillUpdated.Broadcast(Skill->SkillName);
		CheckSkilllvlUp(*Skill);
	}
}

void UPlayerStatsComponent::CheckSkilllvlUp(FSkill& Skill)
{
	const float ExperienceToLvl = 200.0f * Skill.SkillLevel;
	if (Skill.SkillExperience >= ExperienceToLvl)
	{
		Skill.SkillLevel++;
		AddDisciplineExp(Skill.ParentDiscipline, 15.0f * Skill.SkillLevel);
		AddDisciplineExp(Skill.MinorDiscipline, 5.0f * Skill.SkillLevel);
		Skill.SkillExperience = 0.0f;
		OnSkillUpdated.Broadcast(Skill.SkillName);
		switch (Skill.SkillName) 
		{
		case ESkillName::Alchemy:
			break;
		case ESkillName::Balance:
			break;
		case ESkillName::Bartering:
			break;
		case ESkillName::Channeling:
			break;
		case ESkillName::Climbing:
			break;
		case ESkillName::Conjuration:
			break;
		case ESkillName::Dodging:
			break;
		case ESkillName::Hacking:
			break;
		case ESkillName::Invention:
			break;
		case ESkillName::Investigation:
			break;
		case ESkillName::Manipulation:
			break;
		case ESkillName::Manufactor:
			break;
		case ESkillName::MartialCombat:
			break;
		case ESkillName::Medical:
			break;
		case ESkillName::OneHandMartialWeapon:
			break;
		case ESkillName::OneHandProjectileWeapon:
			break;
		case ESkillName::Piloting:
			break;
		case ESkillName::Sprinting:
			if (OwnerCharacter) 
			{
				// Attempt to find the skill in the array
				FSkill* FoundSkill = Skills.FindByKey(ESkillName::Sprinting);
				if (FoundSkill)
				{
					//Add Skill Level * 20 to the MaxWalkSpeed
					OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed += (FoundSkill->SkillLevel * 20.0f);
				}
			}
			break;
		case ESkillName::Stealth:
			break;
		case ESkillName::Swimming:
			break;
		case ESkillName::Throwing:
			break;
		case ESkillName::TwoHandMartialWeapon:
			break;
		case ESkillName::TwoHandProjectileWeapon:
			break;
		case ESkillName::Vaulting:
			if (OwnerCharacter)
			{
				// Attempt to find the skill in the array
				FSkill* FoundSkill = Skills.FindByKey(ESkillName::Vaulting);
				if (FoundSkill)
				{
					//Add Skill Level * 20 to the JumpZVelocity
					OwnerCharacter->GetCharacterMovement()->JumpZVelocity += (FoundSkill->SkillLevel * 20.0f);
				}
			}
			break;
		}
	}
}

int32 UPlayerStatsComponent::GetSkilllvl(ESkillName Skillname)
{
	for (FSkill& Skill : Skills)
	{
		if (Skill.SkillName == Skillname)
		{
			return Skill.SkillLevel;
		}
	}
	return 0;
}

void UPlayerStatsComponent::AddAttributeExp(EAttributeName attributename, float ExptoAdd)
{
	FAttribute* attribute = FindAttributeByName(attributename);
	if (attribute)
	{
		attribute->AttributeExperience += ExptoAdd;
		CheckAttributelvlUp(*attribute);
	}
}

void UPlayerStatsComponent::CheckAttributelvlUp(FAttribute& attribute)
{
	const float ExperienceToLvl = 200.0f * attribute.AttributeLevel;
	if (attribute.AttributeExperience >= ExperienceToLvl)
	{
		attribute.AttributeLevel++;
		CharacterLvlExp += 50 * attribute.AttributeLevel;
		attribute.AttributeExperience = 0.0f;
		OnAttributeUpdated.Broadcast(attribute.AttributeName);
	}
}

int32 UPlayerStatsComponent::GetAttributelvl(EAttributeName Attributename)
{
	for (FAttribute& Attribute : Attributes)
	{
		if (Attribute.AttributeName == Attributename)
		{
			return Attribute.AttributeLevel;
		}
	}
	return 0;
}

void UPlayerStatsComponent::AddDisciplineExp(EDisciplineName Disciplinename, float ExptoAdd)
{
	FDiscipline* discipline = FindDisciplineByName(Disciplinename);
	if (discipline)
	{
		discipline->DisciplineExperience += ExptoAdd;
		CheckDisciplinelvlUp(*discipline);
	}
}

void UPlayerStatsComponent::CheckDisciplinelvlUp(FDiscipline& discipline)
{
	const float ExperienceToLvl = 200.0f * discipline.DisciplineLevel;
	if (discipline.DisciplineExperience >= ExperienceToLvl)
	{
		discipline.DisciplineLevel++;
		AddAttributeExp(discipline.ParentAttribute, 25.0f * discipline.DisciplineLevel);
		discipline.DisciplineExperience = 0.0f;
		OnDisciplineUpdated.Broadcast(discipline.DisciplineName);
	}
}

int32 UPlayerStatsComponent::GetDisciplinelvl(EDisciplineName Disciplinename)
{
	for (FDiscipline& discipline : Disciplines)
	{
		if (discipline.DisciplineName == Disciplinename)
		{
			return discipline.DisciplineLevel;
		}
	}
	return 0;
}

FAttribute* UPlayerStatsComponent::FindAttributeByName(EAttributeName Attributename)
{
	for (FAttribute& Attribute : Attributes)
	{
		if (Attribute.AttributeName == Attributename)
		{
			return &Attribute;
		}
	}
	return nullptr;
}

FDiscipline* UPlayerStatsComponent::FindDisciplineByName(EDisciplineName Disciplinename)
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

FSkill* UPlayerStatsComponent::FindSkillByName(ESkillName Skillname)
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
