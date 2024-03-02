// Fill out your copyright notice in the Description page of Project Settings.


#include "EGA_RavagerBombThrow.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

void UEGA_RavagerBombThrow::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* MontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, BombThrowMontage);
	if (MontagePlay)
	{
		MontagePlay->OnBlendOut.AddDynamic(this, &UEGA_RavagerBombThrow::MontageFinished);
		MontagePlay->OnCancelled.AddDynamic(this, &UEGA_RavagerBombThrow::MontageFinished);
		MontagePlay->OnInterrupted.AddDynamic(this, &UEGA_RavagerBombThrow::MontageFinished);
		MontagePlay->OnCompleted.AddDynamic(this, &UEGA_RavagerBombThrow::MontageFinished);
		MontagePlay->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitHit = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ThrowBombTag, nullptr, false, false);
	if (WaitHit)
	{
		WaitHit->EventReceived.AddDynamic(this, &UEGA_RavagerBombThrow::ThrowBomb);
		WaitHit->ReadyForActivation();
	}
}

void UEGA_RavagerBombThrow::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UEGA_RavagerBombThrow::MontageFinished()
{
	K2_EndAbility();
}

void UEGA_RavagerBombThrow::ThrowBomb(FGameplayEventData Payload)
{
}
