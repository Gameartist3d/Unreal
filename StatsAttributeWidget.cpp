//3DNomad LLC
//engine includes
#include "StatsAttributeWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
//SP includes
#include "FAttribute.h"
#include "FDiscipline.h"
#include "FSkill.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"


void UStatsAttributeWidget::SetSPAttributeData(FAttribute NewAttribute)
{
	SetIconTexture(NewAttribute.AttributeIcon);
	SetStatsNameTextBox(GetAttributeEnumText(NewAttribute.AttributeName));
	SetLevelTextBox(FText::AsNumber(NewAttribute.AttributeLevel));
	float Progress = 0.f;
	if (NewAttribute.AttributeExperienceToLvl != 0)
	{
		Progress = NewAttribute.AttributeExperience / NewAttribute.AttributeExperienceToLvl;
	}
	SetLevelProgressBar(Progress);
}

void UStatsAttributeWidget::SetDisciplineData(FDiscipline NewDiscipline)
{
	SetIconTexture(NewDiscipline.DisciplineIcon);
	SetStatsNameTextBox(GetDisciplineEnumText(NewDiscipline.DisciplineName));
	SetLevelTextBox(FText::AsNumber(NewDiscipline.DisciplineLevel));
	float Progress = 0.f;
	if (NewDiscipline.DisciplineExperienceToLvl != 0)
	{
		Progress = NewDiscipline.DisciplineExperience / NewDiscipline.DisciplineExperienceToLvl;
	}
	SetLevelProgressBar(Progress);
}

void UStatsAttributeWidget::SetSkillData(FSkill NewSkill)
{
	SetIconTexture(NewSkill.SkillIcon);
	SetStatsNameTextBox(GetSkillEnumText(NewSkill.SkillName));
	SetLevelTextBox(FText::AsNumber(NewSkill.SkillLevel));
	float Progress = 0.f;
	if (NewSkill.SkillExperienceToLvl != 0)
	{
		Progress = NewSkill.SkillExperience / NewSkill.SkillExperienceToLvl;
	}
	SetLevelProgressBar(Progress);
}

void UStatsAttributeWidget::SetLevelTextBox(const FText NewLevel) const
{
	LevelTextBox->SetText(NewLevel);
}

void UStatsAttributeWidget::SetIconTexture(UTexture2D* NewTexture) const
{
	if (NewTexture)
	{
		StatsIcon->SetBrushFromTexture(NewTexture);
	}
}

void UStatsAttributeWidget::SetLevelProgressBar(const float NewPercent) const
{
	LevelProgressBar->SetPercent(NewPercent);
}

void UStatsAttributeWidget::SetStatsNameTextBox(const FText& NewStatsName) const
{
	StatsNameTextBox->SetText(NewStatsName);
}

FText UStatsAttributeWidget::GetAttributeEnumText(EAttributeName IncomingAttribute) const
{
	switch (IncomingAttribute)
	{
	case EAttributeName::Physical:
	return FText::FromString("Physical");
	case EAttributeName::Mental:
	return FText::FromString("Mental");
	default:
		return FText::FromString("Whutoh Raggie!");
	}
}

FText UStatsAttributeWidget::GetDisciplineEnumText(EDisciplineName IncomingDiscipline) const
{
	switch (IncomingDiscipline)
	{
	case EDisciplineName::Endurance:
		return FText::FromString("Endurance");
	case EDisciplineName::Flexibility:
		return FText::FromString("Flexibility");
	case EDisciplineName::Mechanical:
		return FText::FromString("Mechanical");
	case EDisciplineName::Reflex:
		return FText::FromString("Reflex");
	case EDisciplineName::Social:
		return FText::FromString("Social");
	case EDisciplineName::Spiritual:
		return FText::FromString("Spiritual");
	case EDisciplineName::Strength:
		return FText::FromString("Strength");
	case EDisciplineName::Technical:
		return FText::FromString("Technical");
	default:
		return FText::FromString("Whutoh Raggie!");
	}
}

FText UStatsAttributeWidget::GetSkillEnumText(ESkillName IncomingSkill) const
{
	switch (IncomingSkill)
	{
	case ESkillName::Alchemy:
		return FText::FromString("Alchemy");
	case ESkillName::Balance:
		return FText::FromString("Balance");
	case ESkillName::Bartering:
		return FText::FromString("Bartering");
	case ESkillName::Channeling:
		return FText::FromString("Channeling");
	case ESkillName::Climbing:
		return FText::FromString("Climbing");
	case ESkillName::Conjuration:
		return FText::FromString("Conjuration");
	case ESkillName::Dodging:
		return FText::FromString("Dodging");
	case ESkillName::Hacking:
		return FText::FromString("Hacking");
	case ESkillName::Invention:
		return FText::FromString("Invention");
	case ESkillName::Investigation:
		return FText::FromString("Investigation");
	case ESkillName::Manipulation:
		return FText::FromString("Manipulation");
	case ESkillName::Manufactor:
		return FText::FromString("Manufactor");
	case ESkillName::Medical:
		return FText::FromString("Medical");
	case ESkillName::Piloting:
		return FText::FromString("Piloting");
	case ESkillName::Sprinting:
		return FText::FromString("Sprinting");
	case ESkillName::Stealth:
		return FText::FromString("Stealth");
	case ESkillName::Swimming:
		return FText::FromString("Swimming");
	case ESkillName::Throwing:
		return FText::FromString("Throwing");
	case ESkillName::Vaulting:
		return FText::FromString("Vaulting");
	case ESkillName::MartialCombat:
		return FText::FromString("MartialCombat");
	case ESkillName::OneHandMartialWeapon:
		return FText::FromString("OneHandMartialWeapon");
	case ESkillName::OneHandProjectileWeapon:
		return FText::FromString("OneHandProjectileWeapon");
	case ESkillName::TwoHandMartialWeapon:
		return FText::FromString("TwoHandMartialWeapon");
	case ESkillName::TwoHandProjectileWeapon:
		return FText::FromString("TwoHandProjectileWeapon");
	default:
		return FText::FromString("Whutoh Raggie!");
	}
}
