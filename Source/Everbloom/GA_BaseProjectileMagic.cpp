// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BaseProjectileMagic.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "BaseProjectile.h"
#include "BaseCharacter.h"
#include "Emilia.h"

void UGA_BaseProjectileMagic::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* MontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, CastMontage);
	if (MontagePlay)
	{
		MontagePlay->OnBlendOut.AddDynamic(this, &UGA_BaseProjectileMagic::MontageFinished);
		MontagePlay->OnCancelled.AddDynamic(this, &UGA_BaseProjectileMagic::MontageFinished);
		MontagePlay->OnInterrupted.AddDynamic(this, &UGA_BaseProjectileMagic::MontageFinished);
		MontagePlay->OnCompleted.AddDynamic(this, &UGA_BaseProjectileMagic::MontageFinished);
		MontagePlay->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* WaitCastComplete = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, CastCompleteTag, nullptr, false, false);
	if (WaitCastComplete)
	{
		WaitCastComplete->EventReceived.AddDynamic(this, &UGA_BaseProjectileMagic::CastComplete);
		WaitCastComplete->ReadyForActivation();
	}
}

void UGA_BaseProjectileMagic::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_BaseProjectileMagic::CastComplete(FGameplayEventData Payload)
{
	UE_LOG(LogTemp, Warning, TEXT("Cast here"));
	AEmilia* em = Cast<AEmilia>(GetAvatarAsCharacter());
	AActor* PotentialLockedOnTarget = em->GetLockedOnTarget();
	//em->LookAtTarget(PotentialLockedOnTarget);
	FActorSpawnParameters Params;
	Params.Owner = GetAvatarAsCharacter();
	ABaseProjectile* Projectile = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, 
		GetAvatarAsCharacter()->GetMesh()->GetSocketTransform("CastSocket"),
		Params);
	Projectile->SetHomingTarget(PotentialLockedOnTarget, Effect);

	K2_EndAbility();
}

void UGA_BaseProjectileMagic::MontageFinished()
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), false, false);
}
