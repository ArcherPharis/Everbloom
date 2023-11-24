// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Quake.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "BaseCharacter.h"
#include "DentonateActor.h"

void UGA_Quake::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_PlayMontageAndWait* CastTargetingMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, CastingMontage);
	if (CastTargetingMontageTask)
	{
		CastTargetingMontageTask->OnBlendOut.AddDynamic(this, &UGA_Quake::MontageInterrupted);
		CastTargetingMontageTask->OnCancelled.AddDynamic(this, &UGA_Quake::MontageInterrupted);
		CastTargetingMontageTask->OnInterrupted.AddDynamic(this, &UGA_Quake::MontageInterrupted);
		CastTargetingMontageTask->OnCompleted.AddDynamic(this, &UGA_Quake::MontageOut);
		CastTargetingMontageTask->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* BeginQuake = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, StartQuakeTag);
	if (BeginQuake)
	{
		BeginQuake->EventReceived.AddDynamic(this, &UGA_Quake::BeginQuake);
		BeginQuake->ReadyForActivation();
	}

}

void UGA_Quake::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UGA_Quake::MontageOut()
{
	K2_EndAbility();
}

void UGA_Quake::MontageInterrupted()
{
	K2_EndAbility();
}

void UGA_Quake::SpawnSystem(float Radius, int NumOfSystems)
{
	FVector PlayerLocation = GetAvatarAsCharacter()->GetBaseLocation()->GetComponentLocation();

    for (int i = 0; i < NumOfSystems; i++)
    {

        FVector SpawnOffset = FVector::ZeroVector;
        SpawnOffset.X = FMath::FRandRange(-Radius, Radius);
        SpawnOffset.Y = FMath::FRandRange(-Radius, Radius);

        FVector SpawnLocation = PlayerLocation + SpawnOffset;

        if (QuakeFX != nullptr)
        {
            FTransform SpawnTransform;
            SpawnTransform.SetLocation(SpawnLocation);

            UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), QuakeFX, SpawnTransform.GetLocation(), SpawnTransform.Rotator(), FVector(5.f,5.f,5.f));

        }
    }

}

void UGA_Quake::ApplyDamageAndForce(FGameplayAbilityTargetDataHandle TargetData)
{
	TArray<AActor*> TargetActors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(TargetData, 0);
	K2_ApplyGameplayEffectSpecToTarget(MakeOutgoingGameplayEffectSpec(QuakeEffect), TargetData);
	LaunchTargets(TargetData);

}

void UGA_Quake::LaunchTargets(const FGameplayAbilityTargetDataHandle& Data)
{

	TArray<AActor*> ComboTargets = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(Data, 0);

	AActor* avatar = GetAvatarActorFromActorInfo();
	ACharacter* avatarAsCharacter = Cast<ACharacter>(avatar);
	avatarAsCharacter->LaunchCharacter(FVector::UpVector * UpwardLaunchSpeed, true, true);


	for (AActor* target : ComboTargets)
	{
		if (target == avatar) continue;

		ACharacter* TargetAsCharacter = Cast<ACharacter>(target);
		if (TargetAsCharacter)
		{
			TargetAsCharacter->LaunchCharacter(FVector::UpVector * UpwardLaunchSpeed, true, true);
		}
	}
}

void UGA_Quake::BeginQuake(FGameplayEventData Payload)
{
	K2_CommitAbility();

	// Spawn the Niagara system at the specified location with the scale
	SpawnSystem(SpikesSpawnRadius, NumOfFXToSpawn);
	ADentonateActor* DA = GetWorld()->SpawnActor<ADentonateActor>(DentActorClass);
	DA->OnExplosion.AddDynamic(this, &UGA_Quake::ApplyDamageAndForce);
	DA->SetActorLocation(GetAvatarAsCharacter()->GetBaseLocation()->GetComponentLocation());
	DA->SendOverlappingActors(GetAvatarAsCharacter());
}
