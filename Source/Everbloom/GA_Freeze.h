// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_Freeze.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_Freeze : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	
	UPROPERTY(EditDefaultsOnly, Category = "Freeze")
	UAnimMontage* CastingMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Freeze")
	FGameplayTag FreezeTimeTag;

	UFUNCTION()
	void MontageOut();

	UFUNCTION()
	void FreezeTime(FGameplayEventData Payload);
};
