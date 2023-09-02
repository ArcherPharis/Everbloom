// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Block.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework./CharacterMovementComponent.h"
#include "BaseCharacter.h"

void UGA_Block::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_PlayMontageAndWait* BlockMontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, BlockMontage);
	if (BlockMontagePlay)
	{
		BlockMontagePlay->OnBlendOut.AddDynamic(this, &UGA_Block::MontageFinished);
		BlockMontagePlay->OnCancelled.AddDynamic(this, &UGA_Block::MontageFinished);
		BlockMontagePlay->OnInterrupted.AddDynamic(this, &UGA_Block::MontageFinished);
		BlockMontagePlay->OnCompleted.AddDynamic(this, &UGA_Block::MontageFinished);
		BlockMontagePlay->ReadyForActivation();
	}
	ACharacter* Chara = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MoveComp = Chara->GetCharacterMovement();
	MoveComp->StopMovementImmediately();

}

void UGA_Block::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_Block::MontageFinished()
{
	K2_EndAbility();
}
