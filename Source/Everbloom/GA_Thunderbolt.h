// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_Thunderbolt.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_Thunderbolt : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	class UAbilityTask_PlayMontageAndWait* CastTargetingMontageTask;

	UPROPERTY(EditDefaultsOnly, Category = "Thunderbolt")
	UAnimMontage* CastingMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Thunderbolt")
	UAnimMontage* TargetingMontage;

	UFUNCTION()
	void TargetingMontageOut();

	UFUNCTION()
	void StartTargeting(FGameplayEventData Payload);

	UFUNCTION()
	void TargetAquired(const FGameplayAbilityTargetDataHandle& Data);

	UFUNCTION()
	void TargetCancelled(const FGameplayAbilityTargetDataHandle& Data);

	UFUNCTION()
	void CastingAnimFinished();

	UPROPERTY(EditDefaultsOnly, Category = "Thunderbolt")
	FGameplayTag StartTargetingTag;

	UPROPERTY(EditDefaultsOnly, Category = "Thunderbolt")
	TSubclassOf<class AGA_ThunderboltTargetActor> TargetActorClass;
	
	void LaunchActorAsCharacter(AActor* Actor, float speed);

	UPROPERTY(EditDefaultsOnly, Category = "Thunderbolt")
	float BlastLaunchSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Thunderbolt")
	TSubclassOf<class UGameplayEffect> LauchBlastEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Thunderbolt")
	FGameplayTag BlastGameplayCueTag;
};
