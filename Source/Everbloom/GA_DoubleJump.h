// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_DoubleJump.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_DoubleJump : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	UPROPERTY(EditDefaultsOnly, Category = "Double Jump")
	UAnimMontage* DoubleJumpMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Double Jump")
	FGameplayTag OnLandTag;

	UPROPERTY(EditDefaultsOnly, Category = "Forces")
	float JumpForce = 400.f;

	UFUNCTION()
	void MontageFinished();


	UFUNCTION()
	void CharacterLanded(FGameplayEventData Payload);
	
};
