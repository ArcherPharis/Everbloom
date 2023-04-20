// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Recipes.generated.h"

USTRUCT(BlueprintType)
struct FRecipe
{
	GENERATED_BODY()
public:
	bool IsCombinationValid(const TArray<class UAbilityFlowerItem*>& Combination) const;
	TSubclassOf<class UGameplayAbility> GetAbilityClass() const {return Abiilty;}
private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UAbilityFlowerItem>> Items;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayAbility> Abiilty;

	bool HasItem(const class UAbilityFlowerItem* item) const;
};
/**
 * 
 */
UCLASS()
class EVERBLOOM_API URecipes : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	TSubclassOf<class UGameplayAbility> GetAbilityForCombination(const TArray<class UAbilityFlowerItem*>& Combination) const;

private:
	UPROPERTY(EditDefaultsOnly)
	TArray<FRecipe> Recipes;
};
