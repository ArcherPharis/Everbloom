// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "AbilityFlower.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API AAbilityFlower : public ABaseItem
{
	GENERATED_BODY()

private:

	virtual void InteractWith(class AEmilia* player) override;
	
};
