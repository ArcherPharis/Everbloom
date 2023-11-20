// Fill out your copyright notice in the Description page of Project Settings.


#include "Dahlia.h"

void ADahlia::HandleCharacterHealth(float NewValue, float MaxHealth)
{
	Super::HandleCharacterHealth(NewValue, MaxHealth);
	if (NewValue <= 0 && !bHasDied)
	{
		OnDahliaDeath();
		bHasDied = true;
	}
}
