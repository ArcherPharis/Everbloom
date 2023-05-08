// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_AttackCombo.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "EBAbilitySystemBlueprintLibrary.h"
#include "BaseCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework./CharacterMovementComponent.h"

void UGA_AttackCombo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	UAbilityTask_PlayMontageAndWait* MontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MeleeMontage);
	if (MontagePlay)
	{
		MontagePlay->OnBlendOut.AddDynamic(this, &UGA_AttackCombo::MontageFinished);
		MontagePlay->OnCancelled.AddDynamic(this, &UGA_AttackCombo::MontageFinished);
		MontagePlay->OnInterrupted.AddDynamic(this, &UGA_AttackCombo::MontageFinished);
		MontagePlay->OnCompleted.AddDynamic(this, &UGA_AttackCombo::MontageFinished);
		MontagePlay->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitComboChange = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ComboChangeTag, nullptr, false, false);
	if (WaitComboChange)
	{
		WaitComboChange->EventReceived.AddDynamic(this, &UGA_AttackCombo::UpdateCombo);
		WaitComboChange->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitComboCommit = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ComboCommitTag, nullptr, false, false);
	if (WaitComboCommit)
	{
		WaitComboCommit->EventReceived.AddDynamic(this, &UGA_AttackCombo::ComboCommit);
		WaitComboCommit->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitHit = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, HitTag, nullptr, false, false);
	if (WaitHit)
	{
		WaitHit->EventReceived.AddDynamic(this, &UGA_AttackCombo::Hit);
		WaitHit->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* PushPlayer = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, PushPlayerTag, nullptr, false, false);
	if (PushPlayer)
	{
		PushPlayer->EventReceived.AddDynamic(this, &UGA_AttackCombo::PushPlayer);
		PushPlayer->ReadyForActivation();
	}
}

void UGA_AttackCombo::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	GetAvatarAsCharacter()->GetCharacterMovement()->SetMovementMode(GetAvatarAsCharacter()->GetCharacterMovement()->GetGroundMovementMode());

}

void UGA_AttackCombo::UpdateCombo(FGameplayEventData Payload)
{
	
	NextComboSectionName = UEBAbilitySystemBlueprintLibrary::GetRandomNameFromTagContainer(Payload.TargetTags);
}

void UGA_AttackCombo::MontageFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee ended"));
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UGA_AttackCombo::ComboCommit(FGameplayEventData Payload)
{
	if (NextComboSectionName == NAME_None)
		return;

	USkeletalMeshComponent* mesh = GetOwningComponentFromActorInfo();
	if (mesh)
	{
		UAnimInstance* AnimBP = mesh->GetAnimInstance();
		if (AnimBP->Montage_GetCurrentSection() == NextComboSectionName)
		{
			return;
		}

		if (AnimBP && AnimBP->GetCurrentActiveMontage())
		{
			UE_LOG(LogTemp, Warning, TEXT("NEXT SECTION!: %s"), *NextComboSectionName.ToString());
			AnimBP->Montage_SetNextSection(AnimBP->Montage_GetCurrentSection(), NextComboSectionName, AnimBP->GetCurrentActiveMontage());
			AnimBP->Montage_JumpToSection(NextComboSectionName, AnimBP->GetCurrentActiveMontage());
		}
	}
}

void UGA_AttackCombo::Hit(FGameplayEventData Payload)
{
	
	if (Payload.TargetData.Num() == 0) return;

	UE_LOG(LogTemp, Warning, TEXT("Hitting Something"));
	TArray<AActor*> TargetActors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(Payload.TargetData, 0);
	for (AActor* TargetActor : TargetActors)
	{
		ACharacter* TargetAsCharacter = Cast<ACharacter>(TargetActor);
		if (TargetAsCharacter)
		{
			TargetAsCharacter->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitPushSpeed * Payload.EventMagnitude, true);
		}
	}

	FGameplayEffectSpecHandle spec = MakeOutgoingGameplayEffectSpec(HitEffect, Payload.EventMagnitude);
	spec.Data.Get()->SetContext(Payload.ContextHandle);

	K2_ApplyGameplayEffectSpecToTarget(spec, Payload.TargetData);
}

void UGA_AttackCombo::PushPlayer(FGameplayEventData Payload)
{
	ACharacter* AvatarAsCharacter = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	AvatarAsCharacter->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitPushSpeed * Payload.EventMagnitude, true);
}
