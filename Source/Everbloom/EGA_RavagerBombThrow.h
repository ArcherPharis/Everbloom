// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "EGA_RavagerBombThrow.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UEGA_RavagerBombThrow : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	UAnimMontage* BombThrowMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	FGameplayTag ThrowBombTag;

	UFUNCTION()
	void MontageFinished();

	UFUNCTION()
	void ThrowBomb(FGameplayEventData Payload);

	UPROPERTY(EditDefaultsOnly, Category = "Bomb Throw")
	TSubclassOf<AActor> BombMeshClass;

	AActor* BombMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Bomb Throw")
	TSubclassOf<AActor> ThrowableBombClass;
};
