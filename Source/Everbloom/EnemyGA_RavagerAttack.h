// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "EnemyGA_RavagerAttack.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UEnemyGA_RavagerAttack : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnTargetHit(AActor* Target);


private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	UAnimMontage* MeleeMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	FGameplayTag HitTag;

	class UCharacterMovementComponent* MovementComp;

	float OrigWalkSpeed;

	UFUNCTION()
	void MontageFinished();

	UFUNCTION()
	void Hit(FGameplayEventData Payload);

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	TSubclassOf<UGameplayEffect> HitEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	float HitPushSpeed = 400.f;
	
};
