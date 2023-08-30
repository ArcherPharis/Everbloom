// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_UseDewfruit.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_UseDewfruit : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	UPROPERTY(EditDefaultsOnly, Category = "Use Dew Fruit")
	UAnimMontage* UseFruitMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Use Dew Fruit")
	TSubclassOf<UGameplayEffect> RestorationEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Use Dew Fruit")
	FGameplayTag UseFruitTag;


	UFUNCTION()
	void UseFruit(FGameplayEventData Payload);

};
