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

	TArray<UAbilityFlowerItem*> SortedCombination = Combination;
	SortedCombination.Sort();

	TArray<TSubclassOf<UAbilityFlowerItem>> SortedFlowerItems = Items;
	SortedFlowerItems.Sort();

	for (int32 i = 0; i < SortedCombination.Num(); i++)
	{
		if (SortedCombination[i]->GetClass() != SortedFlowerItems[i])
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
