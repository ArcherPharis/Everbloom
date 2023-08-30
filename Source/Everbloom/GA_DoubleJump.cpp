// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_DoubleJump.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameFramework./CharacterMovementComponent.h"
#include "BaseCharacter.h"

void UGA_DoubleJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* JumpMontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, DoubleJumpMontage);
	if (JumpMontagePlay)
	{
		JumpMontagePlay->ReadyForActivation();
	}
	ABaseCharacter* Chara = GetAvatarAsCharacter();

	if (Chara->GetCharacterMovement()->IsFalling()) {
		FVector NewVelocity = Chara->GetVelocity();
		NewVelocity.Z = FMath::Max(NewVelocity.Z, 0.0f);
		Chara->GetCharacterMovement()->Velocity = NewVelocity;
	}

	Chara->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorUpVector() * JumpForce, true);

	UAbilityTask_WaitGameplayEvent* LandTagEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, OnLandTag, nullptr, false, false);
	if (LandTagEvent)
	{
		LandTagEvent->EventReceived.AddDynamic(this, &UGA_DoubleJump::CharacterLanded);
		LandTagEvent->ReadyForActivation();
	}
}


void UGA_DoubleJump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UGA_DoubleJump::MontageFinished()
{
	K2_EndAbility();
}

void UGA_DoubleJump::CharacterLanded(FGameplayEventData Payload)
{
	K2_EndAbility();
}
