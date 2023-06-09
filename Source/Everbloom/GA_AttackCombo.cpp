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
	UCharacterMovementComponent* MovementComp = GetAvatarAsCharacter()->GetCharacterMovement();
	MovementComp->GravityScale = 0.0f;
	//MovementComp->DisableMovement();

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
	UCharacterMovementComponent* MovementComp = GetAvatarAsCharacter()->GetCharacterMovement();
	MovementComp->GravityScale = 1.0f;
	//MovementComp->SetMovementMode(EMovementMode::MOVE_Walking);

}

void UGA_AttackCombo::UpdateCombo(FGameplayEventData Payload)
{
	
	NextComboSectionName = UEBAbilitySystemBlueprintLibrary::GetRandomNameFromTagContainer(Payload.TargetTags);
}

void UGA_AttackCombo::MontageFinished()
{
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
			if (NextComboSectionName == TEXT("Combo04"))
			{
				//bAttackPush = true;
			}

			AnimBP->Montage_SetNextSection(AnimBP->Montage_GetCurrentSection(), NextComboSectionName, AnimBP->GetCurrentActiveMontage());
			AnimBP->Montage_JumpToSection(NextComboSectionName, AnimBP->GetCurrentActiveMontage());
		}
	}
}

void UGA_AttackCombo::Hit(FGameplayEventData Payload)
{
	
	if (Payload.TargetData.Num() == 0) return;
	

	TArray<AActor*> TargetActors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(Payload.TargetData, 0);
	for (AActor* TargetActor : TargetActors)
	{
		ACharacter* TargetAsCharacter = Cast<ACharacter>(TargetActor);
		if (TargetAsCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT("NEXT SECTION!: %s"), *NextComboSectionName.ToString());
			if (!TargetAsCharacter->GetMovementComponent()->IsFalling() || bAttackPush && TargetAsCharacter->GetMovementComponent()->IsFalling())
			{
				TargetAsCharacter->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitPushSpeed * Payload.EventMagnitude, true);
			}
			else
			{
				TargetAsCharacter->GetCharacterMovement()->Velocity = FVector(0, 0, 0);
			}
		}
	}

	FGameplayEffectSpecHandle spec = MakeOutgoingGameplayEffectSpec(HitEffect, Payload.EventMagnitude);
	spec.Data.Get()->SetContext(Payload.ContextHandle);
	FGameplayEffectSpecHandle AirSpec = MakeOutgoingGameplayEffectSpec(InAirHitEffect, Payload.EventMagnitude);


	K2_ApplyGameplayEffectSpecToTarget(spec, Payload.TargetData);
	K2_ApplyGameplayEffectSpecToTarget(AirSpec, Payload.TargetData);
}

void UGA_AttackCombo::PushPlayer(FGameplayEventData Payload)
{
	ACharacter* AvatarAsCharacter = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MovementComp = AvatarAsCharacter->GetCharacterMovement();
	MovementComp->StopMovementImmediately();
	if (MovementComp->IsFalling())
	{
		return;
	}
	AvatarAsCharacter->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitPushSpeed * Payload.EventMagnitude/1.8f, true);
}
