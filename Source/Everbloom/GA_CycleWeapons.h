// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_CycleWeapons.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_CycleWeapons : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	UPROPERTY(EditDefaultsOnly, Category = "Cycle Weapons")
	UAnimMontage* CycleMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Cycle Weapons")
	FGameplayTag CycleTag;

	UFUNCTION()
	void MontageEnded();

	UFUNCTION()
	void CycleIndex(FGameplayEventData Payload);

	float WeaponCycleDirection = 1;
	
};
