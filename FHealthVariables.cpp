// Fill out your copyright notice in the Description page of Project Settings.


#include "FHealthVariables.h"

FHealthVariables::FHealthVariables()
{
	HealthVariableName = FText::FromString(TEXT("Body Part"));
	MaxHealth = 100.0f;
	CurHealth = 100.0f;
	DamHealth = 0.0f;
	RecHealth = 0.0f;
	PoisHealth = 0.0f;
}

FHealthVariables::~FHealthVariables()
{
}
