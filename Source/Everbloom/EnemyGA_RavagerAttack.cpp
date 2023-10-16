// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGA_RavagerAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameFramework./CharacterMovementComponent.h"
#include "EBAbilitySystemBlueprintLibrary.h"
#include "BaseEnemy.h"

void UEnemyGA_RavagerAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* MontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MeleeMontage);
	if (MontagePlay)
	{
		MontagePlay->OnBlendOut.AddDynamic(this, &UEnemyGA_RavagerAttack::MontageFinished);
		MontagePlay->OnCancelled.AddDynamic(this, &UEnemyGA_RavagerAttack::MontageFinished);
		MontagePlay->OnInterrupted.AddDynamic(this, &UEnemyGA_RavagerAttack::MontageFinished);
		MontagePlay->OnCompleted.AddDynamic(this, &UEnemyGA_RavagerAttack::MontageFinished);
		MontagePlay->ReadyForActivation();
	}

	MovementComp = GetAvatarAsCharacter()->GetCharacterMovement();
	OrigWalkSpeed = MovementComp->MaxWalkSpeed;
	MovementComp->MaxWalkSpeed = 0.f;

	UAbilityTask_WaitGameplayEvent* WaitHit = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, HitTag, nullptr, false, false);
	if (WaitHit)
	{
		WaitHit->EventReceived.AddDynamic(this, &UEnemyGA_RavagerAttack::Hit);
		WaitHit->ReadyForActivation();
	}
}

void UEnemyGA_RavagerAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	MovementComp->MaxWalkSpeed = OrigWalkSpeed;
}

void UEnemyGA_RavagerAttack::MontageFinished()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}

void UEnemyGA_RavagerAttack::Hit(FGameplayEventData Payload)
{

	UE_LOG(LogTemp, Warning, TEXT("Recieving event"));
	if (Payload.TargetData.Num() == 0) return;

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
