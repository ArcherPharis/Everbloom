// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_Evade.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_Evade : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	
	UFUNCTION()
	void EndMovement(FGameplayEventData Payload);

	UPROPERTY(EditDefaultsOnly, Category = "Evade")
	UAnimMontage* EvadeMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Evade")
	FGameplayTag EndMovementTag;

	UPROPERTY(EditDefaultsOnly, Category = "Evade")
	float ForwardForce = 600.f;


	UPROPERTY(EditDefaultsOnly, Category = "Evade")
	float EvadeSpeed = 600.f;

	float OriginalGroundFriction;


};
