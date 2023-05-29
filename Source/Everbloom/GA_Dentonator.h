// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_Dentonator.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_Dentonator : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	
	UPROPERTY(EditDefaultsOnly, Category = "Dentonate")
	UAnimMontage* CastingMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Dentonate")
	UAnimMontage* DentonateMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Dentonate")
	class UParticleSystem* BombFX;

	UPROPERTY(EditDefaultsOnly, Category = "Dentonate")
	class UParticleSystem* ExplosionFX;

	UPROPERTY(EditDefaultsOnly, Category = "Dentonate")
	TSubclassOf<class ADentonateActor> DentActorClass;



	void LaunchActorAsCharacter(AActor* Actor, float speed);

	UPROPERTY(EditDefaultsOnly, Category = "Dentonate")
	float BlastLaunchSpeed = 3500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Dentonate")
	TSubclassOf<class UGameplayEffect> ExplosionEffect;
	
	UPROPERTY()
	UParticleSystemComponent* PartComp;

	FVector BombLocation;

	UFUNCTION()
	void TargetingMontageOut();

	UFUNCTION()
	void SpawnBomb();

	UFUNCTION()
	void DentonateBomb(float time);

	UFUNCTION()
	void ApplyDamageAndForce(FGameplayAbilityTargetDataHandle TargetData);
};
