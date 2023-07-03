// Fill out your copyright notice in the Description page of Project Settings.


#include "FloriologyRecipes.h"
#include "AbilityFlowerItem.h"
#include "EBGameplayAbilityBase.h"

bool FRecipe::IsCombinationValid(const TArray<class UAbilityFlowerItem*>& Combination) const
{
	if (Combination.Num() != Items.Num())
	{
		return false;
	}

	TArray<TSubclassOf<UAbilityFlowerItem>> RemainingItems = Items;

	for (UAbilityFlowerItem* CombinationItem : Combination)
	{
		bool bItemFound = false;

		for (int32 i = 0; i < RemainingItems.Num(); i++)
		{
			if (CombinationItem->GetClass() == RemainingItems[i])
			{
				bItemFound = true;
				RemainingItems.RemoveAt(i);
				break;
			}
		}

		if (!bItemFound)
		{
			return false;
		}
	}

	return true;
}

bool FRecipe::HasItem(const UAbilityFlowerItem* item) const
{
	for (const auto& recipe : Items)
	{
		if (recipe == item->GetClass())
		{
			return true;
		}
	}
	return false;
}

TSubclassOf<class UEBGameplayAbilityBase> UFloriologyRecipes::GetAbilityForCombination(const TArray<class UAbilityFlowerItem*>& Combination) const
{
	for (const auto& Recipe : Recipes)
	{
		if (Recipe.IsCombinationValid(Combination))
		{
			return Recipe.GetAbilityClass();
		}
	}

	return nullptr;
}
