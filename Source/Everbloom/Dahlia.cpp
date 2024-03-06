// Fill out your copyright notice in the Description page of Project Settings.


#include "Dahlia.h"
#include "EBAbilitySystemComponent.h"

void ADahlia::TryUsingRandomSpecialAbility()
{
	if (BossSpecialAbilities.Num() > 0)
	{
		int randomAbilityIndex = FMath::RandRange(0, BossSpecialAbilities.Num() - 1);
		GetAbilitySystemComponent()->TryActivateAbilityByClass(BossSpecialAbilities[randomAbilityIndex]);
	}
}

void ADahlia::BeginPlay()
{
	Super::BeginPlay();
	GiveSpecialAbilities();
}

void ADahlia::HandleCharacterHealth(float NewValue, float MaxHealth)
{
	Super::HandleCharacterHealth(NewValue, MaxHealth);
	if (NewValue <= 0 && !bHasDied)
	{
		OnDahliaDeath();
		OnDeath.Broadcast();
		bHasDied = true;
	}
}

void ADahlia::GiveSpecialAbilities()
{
	for (TSubclassOf<UGameplayAbility> Ability : BossSpecialAbilities)
	{
		GiveAbility(Ability);
	}
}
