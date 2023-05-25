// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Thunderbolt.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "BaseCharacter.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GA_ThunderboltTargetActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UGA_Thunderbolt::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	if (!K2_CheckAbilityCooldown())
	{
		return;
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CastTargetingMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, TargetingMontage);
	if (CastTargetingMontageTask)
	{
		CastTargetingMontageTask->OnBlendOut.AddDynamic(this, &UGA_Thunderbolt::TargetingMontageOut);
		CastTargetingMontageTask->OnCancelled.AddDynamic(this, &UGA_Thunderbolt::TargetingMontageOut);
		CastTargetingMontageTask->OnInterrupted.AddDynamic(this, &UGA_Thunderbolt::TargetingMontageOut);
		CastTargetingMontageTask->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitTargetStart = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, StartTargetingTag);
	if (WaitTargetStart)
	{
		WaitTargetStart->EventReceived.AddDynamic(this, &UGA_Thunderbolt::StartTargeting);
		WaitTargetStart->ReadyForActivation();
	}

}

void UGA_Thunderbolt::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ABaseCharacter* CBase = GetAvatarAsCharacter();
	if (CBase)
	{
		CBase->EnableAiming(false);
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Thunderbolt::TargetingMontageOut()
{
	K2_EndAbility();
}

void UGA_Thunderbolt::StartTargeting(FGameplayEventData Payload)
{
	ABaseCharacter* CBase = GetAvatarAsCharacter();
	if (CBase)
	{
		CBase->EnableAiming(true);
	}

	UAbilityTask_WaitTargetData* WaitTargetData = UAbilityTask_WaitTargetData::WaitTargetData(this, NAME_None, EGameplayTargetingConfirmation::UserConfirmed, TargetActorClass);
	WaitTargetData->ValidData.AddDynamic(this, &UGA_Thunderbolt::TargetAquired);
	WaitTargetData->Cancelled.AddDynamic(this, &UGA_Thunderbolt::TargetCancelled);
	WaitTargetData->ReadyForActivation();

	AGameplayAbilityTargetActor* TargetActor;
	WaitTargetData->BeginSpawningActor(this, TargetActorClass, TargetActor);
	WaitTargetData->FinishSpawningActor(this, TargetActor);
}

void UGA_Thunderbolt::TargetAquired(const FGameplayAbilityTargetDataHandle& Data)
{
	CastTargetingMontageTask->EndTask();
	K2_CommitAbility();
	UAbilityTask_PlayMontageAndWait* CastingMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, CastingMontage);
	if (CastingMontageTask)
	{
		CastingMontageTask->OnBlendOut.AddDynamic(this, &UGA_Thunderbolt::CastingAnimFinished);
		CastingMontageTask->OnCancelled.AddDynamic(this, &UGA_Thunderbolt::CastingAnimFinished);
		CastingMontageTask->OnInterrupted.AddDynamic(this, &UGA_Thunderbolt::CastingAnimFinished);
		CastingMontageTask->OnCompleted.AddDynamic(this, &UGA_Thunderbolt::CastingAnimFinished);
		CastingMontageTask->ReadyForActivation();
	}

	TArray<AActor*> targetActors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(Data, 1);
	for (auto targetActor : targetActors)
	{
		LaunchActorAsCharacter(targetActor, BlastLaunchSpeed);
	}

	K2_ApplyGameplayEffectSpecToTarget(MakeOutgoingGameplayEffectSpec(LauchBlastEffect), Data);
	
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo_Checked();
	FGameplayCueParameters gameplayCueParam;
	gameplayCueParam.Location = Data.Get(0)->GetEndPoint();
	ASC->AddGameplayCue(BlastGameplayCueTag, gameplayCueParam);
}

void UGA_Thunderbolt::TargetCancelled(const FGameplayAbilityTargetDataHandle& Data)
{
	K2_EndAbility();
}

void UGA_Thunderbolt::CastingAnimFinished()
{
	K2_EndAbility();
}

void UGA_Thunderbolt::LaunchActorAsCharacter(AActor* Actor, float speed)
{
	ACharacter* actorAsCharacter = Cast<ACharacter>(Actor);
	if (actorAsCharacter)
	{
		actorAsCharacter->LaunchCharacter(FVector::UpVector * speed, true, true);
	}
}
