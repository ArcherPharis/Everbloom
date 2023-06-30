// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_BaseProjectileMagic.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_BaseProjectileMagic : public UEBGameplayAbilityBase
{
	GENERATED_BODY()
	
private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION()
	void CastComplete(FGameplayEventData Payload);

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	UAnimMontage* CastMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	FGameplayTag CastCompleteTag;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class ABaseProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<UGameplayEffect> Effect;

	UFUNCTION()
	void MontageFinished();
};
