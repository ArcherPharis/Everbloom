// Fill out your copyright notice in the Description page of Project Settings.


#include "Recipes.h"

#include "AbilityFlowerItem.h"

bool FRecipe::IsCombinationValid(const TArray<UAbilityFlowerItem*>& Combination) const
{
	for(const auto& item : Combination)
	{
		if(!HasItem(item))
		{
			return false;
		}
	}

	return Combination.Num() == Items.Num();
}

bool FRecipe::HasItem(const UAbilityFlowerItem* item) const
{
	for(const auto& recipe : Items)
	{
		if(recipe == item->GetClass())
		{
			return true;
		}
	}
	return false;
}

TSubclassOf<UGameplayAbility> URecipes::GetAbilityForCombination(const TArray<UAbilityFlowerItem*>& Combination) const
{
	for(const auto& Recipe : Recipes)
	{
		if(Recipe.IsCombinationValid(Combination))
		{
			return Recipe.GetAbilityClass();
		}
	}

	return nullptr;
}
