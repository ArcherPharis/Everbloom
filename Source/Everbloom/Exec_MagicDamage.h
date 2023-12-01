// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "Exec_MagicDamage.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UExec_MagicDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExec_MagicDamage();
	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage = 30.f;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag EventTag;


	
};
