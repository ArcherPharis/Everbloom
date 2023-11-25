// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_Block.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_Block : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnBlock(const AActor* Attacker);

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	UPROPERTY(EditDefaultsOnly, Category = "Block")
	UAnimMontage* BlockMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Block")
	FGameplayTag EnableBlockingStatusTag;
	UPROPERTY(EditDefaultsOnly, Category = "Block")
	FGameplayTag DisableBlockingStatusTag;
	UPROPERTY(EditDefaultsOnly, Category = "Block")
	FGameplayTag BlockEventTag;
	UPROPERTY(EditDefaultsOnly, Category = "Block")
	TSubclassOf<UGameplayEffect> BlockEffect;
	UPROPERTY(EditDefaultsOnly, Category = "Block")
	TSubclassOf<UGameplayEffect> RemoveBlockEffect;

	UFUNCTION()
	void MontageFinished();

	UFUNCTION()
	void EnableBlockStatus(FGameplayEventData Data);

	UFUNCTION()
	void DisableBlockStatus(FGameplayEventData Data);

	UFUNCTION()
	void PlayerIsBlocking(FGameplayEventData Data);

	
};
