// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_GroundSlam.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_GroundSlam : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	
	UPROPERTY(EditDefaultsOnly, Category = "Air Attack")
	UAnimMontage* AirRiseMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Air Attack")
	UAnimMontage* FallingLoopMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Air Attack")
	UAnimMontage* SlamMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Air Attack")
	FGameplayTag BeginSlamTag;
	UPROPERTY(EditDefaultsOnly, Category = "Air Attack")
	FGameplayTag OnLandTag;
	UPROPERTY(EditDefaultsOnly, Category = "Air Attack")
	FGameplayTag MovementToBlockTag;

	UPROPERTY(EditDefaultsOnly, Category = "Air Attack")
	TSubclassOf<UGameplayEffect> OnLandDamageEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Air Attack")
	TSubclassOf<class ADentonateActor> LandingDamageDetection;

	UPROPERTY(EditDefaultsOnly, Category = "Forces")
	float ForwardAttackForce = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = "Forces")
	float RiseAmountModifier = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = "Forces")
	float DownwardsForce = 600.f;
	UPROPERTY(EditDefaultsOnly, Category = "Forces")
	float TargetLaunchSpeed = 600.f;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	class UNiagaraSystem* LandFX;

	UFUNCTION()
	void MontageFinished();

	UFUNCTION()
	void BeginSlam(FGameplayEventData Payload);

	UFUNCTION()
	void Slam(FGameplayEventData Payload);

	UFUNCTION()
	void ApplyDamageAndForce(FGameplayAbilityTargetDataHandle TargetData);

	void LaunchActorAsCharacter(AActor* Actor, float speed);
};
