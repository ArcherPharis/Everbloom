// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Explosion.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "EBAbilitySystemBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DentonateActor.h"
#include "BaseCharacter.h"

void UGA_Explosion::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* ExplosionMontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ExplosionMontage);
	if (ExplosionMontagePlay)
	{
		ExplosionMontagePlay->OnBlendOut.AddDynamic(this, &UGA_Explosion::MontageFinished);
		ExplosionMontagePlay->OnCancelled.AddDynamic(this, &UGA_Explosion::MontageFinished);
		ExplosionMontagePlay->OnInterrupted.AddDynamic(this, &UGA_Explosion::MontageFinished);
		ExplosionMontagePlay->OnCompleted.AddDynamic(this, &UGA_Explosion::MontageFinished);
		ExplosionMontagePlay->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* ExplodeEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, ExplosionTag, nullptr, false, false);
	if (ExplodeEvent)
	{
		ExplodeEvent->EventReceived.AddDynamic(this, &UGA_Explosion::Explode);
		ExplodeEvent->ReadyForActivation();
	}

}

void UGA_Explosion::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UGA_Explosion::MontageFinished()
{
	K2_EndAbility();
}

void UGA_Explosion::Explode(FGameplayEventData Payload)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFX, GetAvatarActorFromActorInfo()->GetActorLocation(), FRotator::ZeroRotator, FVector(5, 5, 5));
	ADentonateActor* DA = GetWorld()->SpawnActor<ADentonateActor>(ExplosionDetection);
	DA->OnExplosion.AddDynamic(this, &UGA_Explosion::ApplyDamageAndForce);
	DA->SetActorLocation(GetAvatarAsCharacter()->GetActorLocation());
	DA->SendOverlappingActors(GetAvatarAsCharacter());
	OnExplosionEvent();
}

void UGA_Explosion::ApplyDamageAndForce(FGameplayAbilityTargetDataHandle TargetData)
{
	TArray<AActor*> TargetActors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(TargetData, 0);
	for (auto targetActor : TargetActors)
	{
		LaunchActorAsCharacter(targetActor, TargetLaunchSpeed);
	}
	K2_ApplyGameplayEffectSpecToTarget(MakeOutgoingGameplayEffectSpec(DamageEffect), TargetData);
}

void UGA_Explosion::LaunchActorAsCharacter(AActor* Actor, float Speed)
{
	ACharacter* actorAsCharacter = Cast<ACharacter>(Actor);
	if (actorAsCharacter)
	{
		FVector LaunchDirection = actorAsCharacter->GetActorLocation() - GetAvatarActorFromActorInfo()->GetActorLocation();
		FVector LaunchImpulse = LaunchDirection.GetSafeNormal() * Speed;
		actorAsCharacter->LaunchCharacter(LaunchImpulse, true, true);
	}
}
