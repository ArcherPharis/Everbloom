// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItemObject.h"
#include "AbilityFlowerItem.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UAbilityFlowerItem : public UBaseItemObject
{
	GENERATED_BODY()

public:
	TMap<TSubclassOf<UAbilityFlowerItem>, TSubclassOf<class UGameplayAbility>> GetFlowerCraftingRecipes() const { return FloriologyRecipes; }

private:

	//each flower item knows of all of its recipes and what flower is must be partnered with to give the player
	//an ability.
	UPROPERTY(EditDefaultsOnly, Category = "Floriology Crafting")
	TMap<TSubclassOf<UAbilityFlowerItem>, TSubclassOf<UGameplayAbility>> FloriologyRecipes;
	
	
};
