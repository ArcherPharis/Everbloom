// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Freeze.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"

void UGA_Freeze::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* CastTargetingMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, CastingMontage);
	if (CastTargetingMontageTask)
	{

		CastTargetingMontageTask->OnCancelled.AddDynamic(this, &UGA_Freeze::MontageOut);
		CastTargetingMontageTask->OnInterrupted.AddDynamic(this, &UGA_Freeze::MontageOut);
		CastTargetingMontageTask->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitToFreezeTime = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FreezeTimeTag, nullptr, false, false);
	if (WaitToFreezeTime)
	{
		WaitToFreezeTime->EventReceived.AddDynamic(this, &UGA_Freeze::FreezeTime);
		WaitToFreezeTime->ReadyForActivation();
	}

}

void UGA_Freeze::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UGA_Freeze::MontageOut()
{
	K2_EndAbility();
}

void UGA_Freeze::FreezeTime(FGameplayEventData Payload)
{
	
}
