// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Evade.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "BaseCharacter.h"
#include "GameFramework./CharacterMovementComponent.h"



void UGA_Evade::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//BrakingDeccelerationWalking and GroundFriction to 0
	ACharacter* Chara = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MoveComp = Chara->GetCharacterMovement();
	if (MoveComp->IsFalling())
	{
		//K2_EndAbility();
		//return;
	}
	OriginalBrakingWalkingSpeed = MoveComp->BrakingDecelerationWalking;
	OriginalGroundFriction = MoveComp->GroundFriction;

	MoveComp->BrakingDecelerationWalking = 0;
	MoveComp->GroundFriction = 0;
	MoveComp->AddImpulse(Chara->GetActorForwardVector() * ForwardForce, false);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* EvadeMontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, EvadeMontage);
	if (EvadeMontagePlay)
	{
		EvadeMontagePlay->OnBlendOut.AddDynamic(this, &UGA_Evade::K2_EndAbility);
		EvadeMontagePlay->OnCancelled.AddDynamic(this, &UGA_Evade::K2_EndAbility);
		EvadeMontagePlay->OnInterrupted.AddDynamic(this, &UGA_Evade::K2_EndAbility);
		EvadeMontagePlay->OnCompleted.AddDynamic(this, &UGA_Evade::K2_EndAbility);
		EvadeMontagePlay->ReadyForActivation();
	}

}

void UGA_Evade::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	ACharacter* Chara = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MoveComp = Chara->GetCharacterMovement();
	MoveComp->BrakingDecelerationWalking = OriginalBrakingWalkingSpeed;
	MoveComp->GroundFriction = OriginalGroundFriction;

}
