// Copyright Epic Games, Inc. All Rights Reserved.


#include "EverbloomGameModeBase.h"
#include "FloriologyRecipes.h"

TSubclassOf<class UEBGameplayAbilityBase> AEverbloomGameModeBase::GetAbilityForCombination(TArray<class UAbilityFlowerItem*> Items) const
{
	return Recipes->GetAbilityForCombination(Items);
}

TArray<FRecipe> AEverbloomGameModeBase::GetFlowerRecipes() const
{
	return Recipes->GetRecipes();
}

UAbilityFlowerItem* AEverbloomGameModeBase::GetRemainingFlowerFromRecipe(FRecipe Recipe, TSubclassOf<UAbilityFlowerItem> FlowerItemClass)
{
    const TArray<TSubclassOf<UAbilityFlowerItem>>& RecipeItems = Recipe.GetItems();

    if (RecipeItems[0] == RecipeItems[1])
    {
        return FlowerItemClass.GetDefaultObject();
    }

    for (TSubclassOf<UAbilityFlowerItem> RecipeItem : RecipeItems)
    {
        if (RecipeItem != FlowerItemClass)
        {
            return RecipeItem.GetDefaultObject();
        }
    }
    return nullptr;


}

