// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_CycleWeapons.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Emilia.h"
#include "InventoryComponent.h"

void UGA_CycleWeapons::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* CycleMontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, CycleMontage);
	if (CycleMontagePlay)
	{
		CycleMontagePlay->OnCancelled.AddDynamic(this, &UGA_CycleWeapons::K2_EndAbility);
		CycleMontagePlay->OnInterrupted.AddDynamic(this, &UGA_CycleWeapons::K2_EndAbility);
		CycleMontagePlay->OnCompleted.AddDynamic(this, &UGA_CycleWeapons::MontageEnded);
		CycleMontagePlay->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* LandTagEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, CycleTag, nullptr, false, false);
	if (LandTagEvent)
	{
		LandTagEvent->EventReceived.AddDynamic(this, &UGA_CycleWeapons::CycleIndex);
		LandTagEvent->ReadyForActivation();
	}
}

void UGA_CycleWeapons::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_CycleWeapons::MontageEnded()
{
	UE_LOG(LogTemp, Warning, TEXT("Reaching here"));
	AEmilia* Emilia = Cast<AEmilia>(GetAvatarAsCharacter());
	Emilia->GetInventoryComponent()->CycleWeapons(WeaponCycleDirection);
	K2_EndAbility();
}

void UGA_CycleWeapons::CycleIndex(FGameplayEventData Payload)
{
	WeaponCycleDirection = Payload.EventMagnitude;
	UE_LOG(LogTemp, Warning, TEXT("%f"), WeaponCycleDirection);
}
