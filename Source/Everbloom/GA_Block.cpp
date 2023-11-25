// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Block.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameFramework./CharacterMovementComponent.h"
#include "BaseCharacter.h"
#include "Kismet/KismetMathLibrary.h"


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
	UAbilityTask_WaitGameplayEvent* EnableStatusEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EnableBlockingStatusTag, nullptr, false, false);
	if (EnableStatusEvent)
	{
		EnableStatusEvent->EventReceived.AddDynamic(this, &UGA_Block::EnableBlockStatus);
		EnableStatusEvent->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* DisableStatusEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, DisableBlockingStatusTag, nullptr, false, false);
	if (DisableStatusEvent)
	{
		DisableStatusEvent->EventReceived.AddDynamic(this, &UGA_Block::DisableBlockStatus);
		DisableStatusEvent->ReadyForActivation();
	}
	UAbilityTask_WaitGameplayEvent* BlockEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, BlockEventTag, nullptr, false, false);
	if (BlockEvent)
	{
		BlockEvent->EventReceived.AddDynamic(this, &UGA_Block::PlayerIsBlocking);
		BlockEvent->ReadyForActivation();
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

void UGA_Block::EnableBlockStatus(FGameplayEventData Data)
{
	K2_ApplyGameplayEffectSpecToOwner(MakeOutgoingGameplayEffectSpec(BlockEffect));
}

void UGA_Block::DisableBlockStatus(FGameplayEventData Data)
{
	K2_ApplyGameplayEffectSpecToOwner(MakeOutgoingGameplayEffectSpec(RemoveBlockEffect));

}

void UGA_Block::PlayerIsBlocking(FGameplayEventData Data)
{

	AActor* BlockingChara = GetAvatarActorFromActorInfo();
	const AActor* AttackingChara = Data.Instigator.Get();
	FRotator Rotat = UKismetMathLibrary::FindLookAtRotation(BlockingChara->GetActorLocation(), AttackingChara->GetActorLocation());
	Rotat.Pitch = 0.f;
	BlockingChara->SetActorRotation(Rotat);
	OnBlock(AttackingChara);
}
