// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Moonbeam.h"
#include "BaseCharacter.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "EBAbilitySystemComponent.h"

void UGA_Moonbeam::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//if (!CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, false, false))
	//	return;
	//GetAvatarAsCharacter()->GetAbilitySystemComponent()->NotifyAbilityCommit(this);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_PlayMontageAndWait* PlayBeamMontage = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, BeamMontage);
	if (PlayBeamMontage)
	{
		PlayBeamMontage->OnBlendOut.AddDynamic(this, &UGA_Moonbeam::EndBeamMontage);
		PlayBeamMontage->OnCancelled.AddDynamic(this, &UGA_Moonbeam::EndBeamMontage);
		PlayBeamMontage->OnCompleted.AddDynamic(this, &UGA_Moonbeam::EndBeamMontage);
		PlayBeamMontage->OnInterrupted.AddDynamic(this, &UGA_Moonbeam::EndBeamMontage);
		PlayBeamMontage->ReadyForActivation();
	}
	UAbilityTask_WaitGameplayEvent* BeginFiringBeamEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, StartFiringBeamTag);
	if (BeginFiringBeamEvent)
	{
		BeginFiringBeamEvent->EventReceived.AddDynamic(this, &UGA_Moonbeam::FireMoonbeam);
		BeginFiringBeamEvent->ReadyForActivation();
	}
}

void UGA_Moonbeam::EndBeamMontage()
{
	K2_EndAbility();
}

void UGA_Moonbeam::FireMoonbeam(FGameplayEventData Payload)
{
	UAbilityTask_WaitTargetData* WaitMoonbeamTarget = UAbilityTask_WaitTargetData::WaitTargetData(this, NAME_None, EGameplayTargetingConfirmation::CustomMulti, MoonbeamActorClass);

	if (WaitMoonbeamTarget)
	{
		//WaitMoonbeamTarget->ValidData.AddDynamic(this, &UGA_Moonbeam::TargetAquired);
		WaitMoonbeamTarget->ReadyForActivation();

		AGameplayAbilityTargetActor* TargetActor;
		WaitMoonbeamTarget->BeginSpawningActor(this, MoonbeamActorClass, TargetActor);

		TargetActor->OwningAbility = this;
		AActor* avatarActor = GetAvatarActorFromActorInfo();
		TargetActor->PostSpawnInitialize(avatarActor->GetActorTransform(), avatarActor, nullptr, false, true, true);

		WaitMoonbeamTarget->FinishSpawningActor(this, TargetActor);

		//TargetActor->AttachToActor(avatarActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		USkeletalMeshComponent* CasterSMC = GetOwningComponentFromActorInfo();
		if (CasterSMC)
		{
			TargetActor->AttachToComponent(CasterSMC, FAttachmentTransformRules::SnapToTargetNotIncludingScale, BeamSlot);
		}
	}
}
