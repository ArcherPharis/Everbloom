// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Exec_PhysicalDamage.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UExec_PhysicalDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag EventTag;

public:
	UExec_PhysicalDamage();
	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const;
	
};
