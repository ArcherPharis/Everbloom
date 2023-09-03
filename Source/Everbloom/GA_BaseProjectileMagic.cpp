// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BaseProjectileMagic.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "BaseProjectile.h"
#include "BaseCharacter.h"
#include "Emilia.h"

void UGA_BaseProjectileMagic::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	AEmilia* Emilia = Cast<AEmilia>(GetAvatarAsCharacter());
	Emilia->StartAim();
}

void UGA_BaseProjectileMagic::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_BaseProjectileMagic::CastComplete(FGameplayEventData Payload)
{

}

void UGA_BaseProjectileMagic::MontageFinished()
{
	
}
