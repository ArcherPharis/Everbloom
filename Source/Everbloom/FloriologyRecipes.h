// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FloriologyRecipes.generated.h"

USTRUCT()
struct FRecipe
{
	GENERATED_BODY()

public:
	bool IsCombinationValid(const TArray<class UAbilityFlowerItem*>& Combination)const;
	TSubclassOf<class UEBGameplayAbilityBase>GetAbilityClass() const { return Ability; }
	TArray<TSubclassOf<class UAbilityFlowerItem>> GetItems() const { return Items; }

private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UAbilityFlowerItem>> Items;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UEBGameplayAbilityBase> Ability;

	bool HasItem(const class UAbilityFlowerItem* item) const;
};



UCLASS()
class EVERBLOOM_API UFloriologyRecipes : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	TSubclassOf<class UEBGameplayAbilityBase> GetAbilityForCombination(const TArray<class UAbilityFlowerItem*>& Combination) const;

	TArray<FRecipe> GetRecipes() const {return Recipes; }
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FRecipe> Recipes;
	
};
