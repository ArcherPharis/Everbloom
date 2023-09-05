// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_Moonbeam.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_Moonbeam : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;


	UPROPERTY(EditDefaultsOnly, Category = "Moonbeam")
	float MoonbeamDuration = 4.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Moonbeam")
	FName BeamSlot;
	UPROPERTY(EditDefaultsOnly, Category = "Moonbeam")
	UAnimMontage* BeamMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Moonbeam")
	FGameplayTag StartFiringBeamTag;

	UPROPERTY(EditDefaultsOnly, Category = "Moonbeam")
	TSubclassOf<class AGameplayAbilityTargetActor> MoonbeamActorClass;

	UFUNCTION()
	void EndBeamMontage();

	UFUNCTION()
	void FireMoonbeam(FGameplayEventData Payload);

	class AEmilia* Emilia;

};
