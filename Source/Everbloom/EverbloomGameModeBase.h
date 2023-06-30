// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FloriologyRecipes.h"
#include "EverbloomGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API AEverbloomGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	TSubclassOf<class UEBGameplayAbilityBase> GetAbilityForCombination(TArray<class UAbilityFlowerItem*> Items)const;
	TArray<FRecipe> GetFlowerRecipes() const;
	class UAbilityFlowerItem* GetRemainingFlowerFromRecipe(FRecipe Recipe, TSubclassOf<UAbilityFlowerItem> FlowerItemClass);

private:
	UPROPERTY(EditDefaultsOnly)
	class UFloriologyRecipes* Recipes;
	
};
