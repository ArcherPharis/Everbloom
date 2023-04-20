// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EverbloomGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API AEverbloomGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	TSubclassOf<class UGameplayAbility> GetAbilityForCombination(TArray<class UAbilityFlowerItem*> Items) const;
private:
	UPROPERTY(EditDefaultsOnly)
	class URecipes* Recipes;
};
