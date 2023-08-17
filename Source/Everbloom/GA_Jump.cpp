// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Jump.h"
#include "BaseCharacter.h"
#include "GameFramework./CharacterMovementComponent.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "EBAbilitySystemComponent.h"


void UGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_WaitGameplayEvent* LandTagEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, OnLandTag, nullptr, false, false);
	if (LandTagEvent)
	{
		LandTagEvent->EventReceived.AddDynamic(this, &UGA_Jump::CharacterLanded);
		LandTagEvent->ReadyForActivation();
	}
	GetAvatarAsCharacter()->Jump();
}

void UGA_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Jump::CharacterLanded(FGameplayEventData Payload)
{
	UE_LOG(LogTemp, Warning, TEXT("Character Landed!"));
	K2_EndAbility();
}
