// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_Quake.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_Quake : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnQuakeActivate();

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	UPROPERTY(EditDefaultsOnly, Category = "Quake")
	TSubclassOf<class ADentonateActor> DentActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Quake")
	UAnimMontage* CastingMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Quake")
	class UNiagaraSystem* QuakeFX;

	UPROPERTY(EditDefaultsOnly, Category = "Quake")
	TSubclassOf<class UGameplayEffect> QuakeEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Quake")
	FGameplayTag StartQuakeTag;


	UPROPERTY(EditDefaultsOnly, Category = "Quake")
	float SpikesSpawnRadius = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Quake")
	int NumOfFXToSpawn = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Quake")
	float UpwardLaunchSpeed = 300.f;

	UFUNCTION()
	void MontageOut();

	UFUNCTION()
	void MontageInterrupted();

	void SpawnSystem(float Radius, int NumOfSystems);

	UFUNCTION()
	void ApplyDamageAndForce(FGameplayAbilityTargetDataHandle TargetData);

	void LaunchTargets(const FGameplayAbilityTargetDataHandle& Data);

	UFUNCTION()
	void BeginQuake(FGameplayEventData Payload);
};
