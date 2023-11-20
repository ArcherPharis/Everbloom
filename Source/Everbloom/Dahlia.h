// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "Dahlia.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API ADahlia : public ABaseEnemy
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnDahliaDeath();

private:
	virtual void HandleCharacterHealth(float NewValue, float MaxHealth) override;

	bool bHasDied = false;
	
};
