// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_Explosion.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_Explosion : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnExplosionEvent();

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	UAnimMontage* ExplosionMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	FGameplayTag ExplosionTag;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	class UParticleSystem* ExplosionFX;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	TSubclassOf<class ADentonateActor> ExplosionDetection;
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	TSubclassOf<UGameplayEffect> DamageEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Forces")
	float TargetLaunchSpeed = 600.f;

	UFUNCTION()
	void MontageFinished();

	UFUNCTION()
	void Explode(FGameplayEventData Payload);

	UFUNCTION()
	void ApplyDamageAndForce(FGameplayAbilityTargetDataHandle TargetData);

	void LaunchActorAsCharacter(AActor* Actor, float speed);
	
};
