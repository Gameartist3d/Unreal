//3DNomad LLC


#include "Spell.h"

USpell::USpell()
{
	SpellTextData.SpellName = ESpellName::Bile;
	SpellTextData.SpellDescription = FText::FromString(TEXT("Generic Spell"));
	SpellTextData.SpellToolTipText = FText::FromString(TEXT("Generic Spell Tooltip"));
	SpellNumericData.SpellCost = 1.0f;
	SpellNumericData.SpellDifficulty = 10.0f;
	SpellNumericData.SpellLevel = 1;
	SpellNumericData.SpellExpToLvl = 100.0f;
	SpellNumericData.SpellCurExp = 0.0f;
}

void USpell::ChannelSpell(AActor* Caster)
{
}

void USpell::OnChannelStutter(AActor* Caster)
{
}

void USpell::OnChannelFail(AActor* Caster)
{
}

void USpell::CastSpell(AActor* Caster)
{
}

void USpell::SpellCastFail(AActor* Caster)
{
}
