// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_ProjectileMagic.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_ProjectileMagic : public UEBGameplayAbilityBase
{
	GENERATED_BODY()
private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	UAnimMontage* CastingMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	FGameplayTag CastMagicTag;

	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	bool bIsRapidFire = false;

	UPROPERTY(EditDefaultsOnly, Category = "Casting")
	TSubclassOf<UGameplayEffect> EffectToApply;

	UFUNCTION()
	void MontageFinished();

	UFUNCTION()
	void CastProjectile(FGameplayEventData Payload);

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class ABaseProjectile> ProjectileClass;
	
};
