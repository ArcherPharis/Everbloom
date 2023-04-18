// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_AttackCombo.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "EBAbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework./CharacterMovementComponent.h"

void UGA_AttackCombo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
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
}

void UGA_AttackCombo::UpdateCombo(FGameplayEventData Payload)
{
	UE_LOG(LogTemp, Warning, TEXT("we updating"));
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

	bAttackPush = false;
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
	if (!bAttackPush)
	{
		bAttackPush = true;
		ACharacter* AvatarAsCharacter = Cast<ACharacter>(GetAvatarActorFromActorInfo());
		AvatarAsCharacter->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitPushSpeed * Payload.EventMagnitude, true);

	}

	TArray<AActor*> TargetActors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(Payload.TargetData, 0);
	for (AActor* TargetActor : TargetActors)
	{
		ACharacter* TargetAsCharacter = Cast<ACharacter>(TargetActor);
		if (TargetAsCharacter)
		{
			TargetAsCharacter->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitPushSpeed * Payload.EventMagnitude, true);
		}
	}

	//FGameplayEffectSpecHandle spec = MakeOutgoingGameplayEffectSpec(HitEffect, Payload.EventMagnitude);
	//spec.Data.Get()->SetContext(Payload.ContextHandle);

	//K2_ApplyGameplayEffectSpecToTarget(spec, Payload.TargetData);
}
