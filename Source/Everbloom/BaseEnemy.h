// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "ITargetingInterface.h"
#include "BaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API ABaseEnemy : public ABaseCharacter, public IITargetingInterface
{
	GENERATED_BODY()

protected:
	virtual void HandleCharacterHealth(float NewValue, float MaxHealth) override;

private:
	virtual void IsTargetable(bool& IsTargetable) override;

	


	
};
