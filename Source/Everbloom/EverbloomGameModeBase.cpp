// Copyright Epic Games, Inc. All Rights Reserved.


#include "EverbloomGameModeBase.h"
#include "FloriologyRecipes.h"

TSubclassOf<class UEBGameplayAbilityBase> AEverbloomGameModeBase::GetAbilityForCombination(TArray<class UAbilityFlowerItem*> Items) const
{
	return Recipes->GetAbilityForCombination(Items);
}
