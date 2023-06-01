// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Quake.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "BaseCharacter.h"

void UGA_Quake::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_PlayMontageAndWait* CastTargetingMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, CastingMontage);
	if (CastTargetingMontageTask)
	{
		CastTargetingMontageTask->OnBlendOut.AddDynamic(this, &UGA_Quake::MontageOut);
		CastTargetingMontageTask->OnCancelled.AddDynamic(this, &UGA_Quake::MontageOut);
		CastTargetingMontageTask->OnInterrupted.AddDynamic(this, &UGA_Quake::MontageOut);
		CastTargetingMontageTask->OnCompleted.AddDynamic(this, &UGA_Quake::MontageOut);
		CastTargetingMontageTask->ReadyForActivation();
	}

}

void UGA_Quake::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UGA_Quake::MontageOut()
{
	K2_CommitAbility();

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetAvatarAsCharacter()->GetActorLocation());
	SpawnTransform.SetScale3D(FVector(50.0f, 50.0f, 50.0f));

	// Spawn the Niagara system at the specified location with the scale
	UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), QuakeFX, SpawnTransform.GetLocation(), SpawnTransform.Rotator());

	K2_EndAbility();
}
