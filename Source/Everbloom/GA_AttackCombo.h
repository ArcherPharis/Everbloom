// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_AttackCombo.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_AttackCombo : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	UAnimMontage* MeleeMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	FGameplayTag ComboChangeTag;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	FGameplayTag ComboCommitTag;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	FGameplayTag HitTag;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	float HitPushSpeed = 200.f;
	UFUNCTION()
	void UpdateCombo(FGameplayEventData Payload);

	UFUNCTION()
	void MontageFinished();

	UFUNCTION()
	void ComboCommit(FGameplayEventData Payload);
	UFUNCTION()
	void Hit(FGameplayEventData Payload);

	FName NextComboSectionName;

	bool bAttackPush;
	
};
