// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_UseDewfruit.h"
#include "EBAbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "BaseCharacter.h"


void UGA_UseDewfruit::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	//if (!CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, false, false))
	//	return;

	if (!CheckCost(Handle, ActorInfo))
		return;


	UAbilityTask_PlayMontageAndWait* UseFruitMontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, UseFruitMontage);
	if (UseFruitMontagePlay)
	{
		UseFruitMontagePlay->OnBlendOut.AddDynamic(this, &UGA_UseDewfruit::K2_EndAbility);
		UseFruitMontagePlay->OnCancelled.AddDynamic(this, &UGA_UseDewfruit::K2_EndAbility);
		UseFruitMontagePlay->OnInterrupted.AddDynamic(this, &UGA_UseDewfruit::K2_EndAbility);
		UseFruitMontagePlay->OnCompleted.AddDynamic(this, &UGA_UseDewfruit::K2_EndAbility);
		UseFruitMontagePlay->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* UseFruitEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, UseFruitTag, nullptr, false, false);
	if (UseFruitEvent)
	{
		UseFruitEvent->EventReceived.AddDynamic(this, &UGA_UseDewfruit::UseFruit);
		UseFruitEvent->ReadyForActivation();
	}

	
}

void UGA_UseDewfruit::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_UseDewfruit::UseFruit(FGameplayEventData Payload)
{
	K2_CommitAbility();
	GetAbilitySystemComponentFromActorInfo()->NotifyAbilityCommit(this);
	ApplyGameplayEffectSpecToOwner(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), MakeOutgoingGameplayEffectSpec(RestorationEffect));
}
