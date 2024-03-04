//3DNomad LLC


#include "FHealthVariables.h"


FHealthVariables::FHealthVariables()
{
	HealthVariableName = ESPHealthVarNames::AssCheek;
	isLeftAppendage = false;
	isRightAppendage = false;
	HVariableIcon = nullptr;
	MaxHealth = 100.0f;
	CurHealth = 100.0f;
	DamHealth = 0.0f;
	RecHealth = 0.0f;
	PoisHealth = 0.0f;
	HeatAmount = 0.0f;
	ColdAmount = 0.0f;
}

FHealthVariables::~FHealthVariables()
{
}
