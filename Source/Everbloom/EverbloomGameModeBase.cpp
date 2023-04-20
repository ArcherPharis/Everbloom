// Copyright Epic Games, Inc. All Rights Reserved.


#include "EverbloomGameModeBase.h"

#include "Recipes.h"

TSubclassOf<UGameplayAbility> AEverbloomGameModeBase::GetAbilityForCombination(TArray<UAbilityFlowerItem*> Items) const
{
	return Recipes->GetAbilityForCombination(Items);
}
