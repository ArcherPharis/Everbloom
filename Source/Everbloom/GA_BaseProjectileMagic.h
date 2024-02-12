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

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Projectile Magic")
	void FireEvent();

	
private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UFUNCTION()
	void DetermineFiring(FGameplayEventData Payload);
	UFUNCTION()
	void EndFromInputRelease(FGameplayEventData Payload);

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	UAnimMontage* AimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	FGameplayTag PlayerInputFireTag;
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	FGameplayTag EndAbilityTag;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<class ABaseProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<UGameplayEffect> Effect;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float FireRate = 30;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<UUserWidget> ReticleClass;

	UUserWidget* Reticle;

	UFUNCTION()
	void MontageFinished();

	void UpdateFireStatus();

	bool bCanFire = false;
	FTimerHandle ShootHandle;
	class AEmilia* Emilia;
};
