// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Dentonator.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "EBAbilitySystemComponent.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "DentonateActor.h"
#include "BaseCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

void UGA_Dentonator::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!K2_CheckAbilityCooldown())
	{
		return;
	}
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_PlayMontageAndWait* CastTargetingMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, CastingMontage);
	if (CastTargetingMontageTask)
	{
		//CastTargetingMontageTask->OnBlendOut.AddDynamic(this, &UGA_Dentonator::TargetingMontageOut);
		CastTargetingMontageTask->OnCancelled.AddDynamic(this, &UGA_Dentonator::TargetingMontageOut);
		CastTargetingMontageTask->OnInterrupted.AddDynamic(this, &UGA_Dentonator::TargetingMontageOut);
		CastTargetingMontageTask->OnCompleted.AddDynamic(this, &UGA_Dentonator::SpawnBomb);
		CastTargetingMontageTask->ReadyForActivation();
	}
}

void UGA_Dentonator::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


void UGA_Dentonator::LaunchActorAsCharacter(AActor* Actor, float Speed)
{
	ACharacter* actorAsCharacter = Cast<ACharacter>(Actor);
	if (actorAsCharacter)
	{
		//FVector LaunchDirection = FVector::UpVector;
		//float PitchAngle = FMath::RandRange(45.f, 270.f);
		//float YawAngle = FMath::RandRange(45.f, 270.f);
		//FRotator LaunchRotation(PitchAngle, YawAngle, 0.f);
		//LaunchDirection = LaunchRotation.RotateVector(LaunchDirection);

		FVector LaunchDirection = FVector::UpVector + FMath::VRandCone(FVector::UpVector, 99.f);

		FVector LaunchImpulse = LaunchDirection.GetSafeNormal() * Speed;
		actorAsCharacter->LaunchCharacter(LaunchImpulse, true, true);
	}
}

void UGA_Dentonator::TargetingMontageOut()
{

	K2_EndAbility();
}

void UGA_Dentonator::SpawnBomb()
{
	BombLocation = GetAvatarAsCharacter()->GetActorLocation();
	PartComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BombFX, BombLocation);
	UAbilityTask_WaitInputPress* WaitTask = UAbilityTask_WaitInputPress::WaitInputPress(this, false);
	if (WaitTask)
	{
		WaitTask->OnPress.AddDynamic(this, &UGA_Dentonator::DentonateBomb);
		WaitTask->ReadyForActivation();

	}
}

void UGA_Dentonator::DentonateBomb(float time)
{
	K2_CommitAbility();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFX, BombLocation, FRotator::ZeroRotator, FVector(5,5,5));
	PartComp->DestroyComponent();
	
	
	ADentonateActor* DA = GetWorld()->SpawnActor<ADentonateActor>(DentActorClass);
	DA->OnExplosion.AddDynamic(this, &UGA_Dentonator::ApplyDamageAndForce);
	DA->SetActorLocation(BombLocation);
	DA->SendOverlappingActors(GetAvatarAsCharacter());

}

void UGA_Dentonator::ApplyDamageAndForce(FGameplayAbilityTargetDataHandle TargetData)
{
	TArray<AActor*> TargetActors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(TargetData, 0);
	for (auto targetActor : TargetActors)
	{
		LaunchActorAsCharacter(targetActor, BlastLaunchSpeed);
	}
	K2_ApplyGameplayEffectSpecToTarget(MakeOutgoingGameplayEffectSpec(ExplosionEffect), TargetData);

	K2_EndAbility();
}
