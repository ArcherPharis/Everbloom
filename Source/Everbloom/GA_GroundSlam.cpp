// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_GroundSlam.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "GameFramework./CharacterMovementComponent.h"
#include "DentonateActor.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Emilia.h"
#include "EBAbilitySystemBlueprintLibrary.h"

void UGA_GroundSlam::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	//there is also a hitbox around the character during the falling phase, will check if those targets
	//are in the air. If they are, send them flying down too. 
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* AirRiseMontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AirRiseMontage);
	if (AirRiseMontagePlay)
	{
		AirRiseMontagePlay->ReadyForActivation();
	}
	ABaseCharacter* Chara = GetAvatarAsCharacter();
	UCharacterMovementComponent* MC = Chara->GetCharacterMovement();
	MC->StopMovementImmediately();
	Chara->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorForwardVector() * ForwardAttackForce, true);
	Chara->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorUpVector() * RiseAmountModifier, true);

	UAbilityTask_WaitGameplayEvent* BeginSlamTagEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, BeginSlamTag, nullptr, false, false);
	if (BeginSlamTagEvent)
	{
		BeginSlamTagEvent->EventReceived.AddDynamic(this, &UGA_GroundSlam::BeginSlam);
		BeginSlamTagEvent->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* LandEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, OnLandTag, nullptr, false, false);
	if (LandEvent)
	{
		LandEvent->EventReceived.AddDynamic(this, &UGA_GroundSlam::Slam);
		LandEvent->ReadyForActivation();
	}
}

void UGA_GroundSlam::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UGA_GroundSlam::MontageFinished()
{
	K2_EndAbility();

}

void UGA_GroundSlam::SendEnemyFlyingDown(FGameplayAbilityTargetDataHandle TargetData)
{
	TArray<AActor*> TargetActors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(TargetData, 0);
	for (auto targetActor : TargetActors)
	{
		UCharacterMovementComponent* MC = Cast<ABaseCharacter>(targetActor)->GetCharacterMovement();
		if (!MC->IsFalling()) return;
		MC->StopMovementImmediately();
		MC->AddImpulse(targetActor->GetActorUpVector() * -DownwardsForce, true);
		K2_ApplyGameplayEffectSpecToTarget(MakeOutgoingGameplayEffectSpec(InAirDamageEffect), TargetData);

	}
}

void UGA_GroundSlam::BeginSlam(FGameplayEventData Payload)
{
	UCharacterMovementComponent* MC = GetAvatarAsCharacter()->GetCharacterMovement();
	MC->StopMovementImmediately();
	MC->AddImpulse(GetAvatarActorFromActorInfo()->GetActorUpVector() * -DownwardsForce, true);
	UAbilityTask_PlayMontageAndWait* FallingMontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, FallingLoopMontage);
	if (FallingMontagePlay)
	{
		//FallingMontagePlay->OnInterrupted.AddDynamic(this, &UGA_GroundSlam::MontageFinished);
		FallingMontagePlay->OnCompleted.AddDynamic(this, &UGA_GroundSlam::MontageFinished);
		FallingMontagePlay->ReadyForActivation();
	}
	BlockAbilitiesWithTag.AddTag(MovementToBlockTag);
	GrabberSphere = GetWorld()->SpawnActor<ADentonateActor>(GrabberSphereClass);
	GrabberSphere->SetOwner(GetAvatarActorFromActorInfo());
	GrabberSphere->SetActorLocation(GetAvatarAsCharacter()->GetActorLocation());
	GrabberSphere->OnActorTouchedSphere.AddDynamic(this, &UGA_GroundSlam::SendEnemyFlyingDown);
	GrabberSphere->SendOverlappingActors(GetAvatarActorFromActorInfo());
}

void UGA_GroundSlam::Slam(FGameplayEventData Payload)
{
	UAbilityTask_PlayMontageAndWait* SlamMontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, SlamMontage);
	if (SlamMontagePlay)
	{
		SlamMontagePlay->OnBlendOut.AddDynamic(this, &UGA_GroundSlam::MontageFinished);
		SlamMontagePlay->OnCancelled.AddDynamic(this, &UGA_GroundSlam::MontageFinished);
		SlamMontagePlay->OnInterrupted.AddDynamic(this, &UGA_GroundSlam::MontageFinished);
		SlamMontagePlay->OnCompleted.AddDynamic(this, &UGA_GroundSlam::MontageFinished);
		SlamMontagePlay->ReadyForActivation();
	}
	ADentonateActor* DA = GetWorld()->SpawnActor<ADentonateActor>(LandingDamageDetection);
	DA->OnExplosion.AddDynamic(this, &UGA_GroundSlam::ApplyDamageAndForce);
	DA->SetActorLocation(GetAvatarAsCharacter()->GetActorLocation());
	DA->SendOverlappingActors(GetAvatarAsCharacter());
	Payload.EventMagnitude = 20.f;
	UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), LandFX, GetAvatarAsCharacter()->GetBaseLocation()->GetComponentLocation(), GetAvatarAsCharacter()->GetBaseLocation()->GetComponentRotation(), FVector(5.f, 5.f, 5.f));
}

void UGA_GroundSlam::ApplyDamageAndForce(FGameplayAbilityTargetDataHandle TargetData)
{
	TArray<AActor*> TargetActors = UAbilitySystemBlueprintLibrary::GetActorsFromTargetData(TargetData, 0);
	for (auto targetActor : TargetActors)
	{
		LaunchActorAsCharacter(targetActor, TargetLaunchSpeed);
	}
	K2_ApplyGameplayEffectSpecToTarget(MakeOutgoingGameplayEffectSpec(OnLandDamageEffect), TargetData);
}

void UGA_GroundSlam::LaunchActorAsCharacter(AActor* Actor, float Speed)
{
	ACharacter* actorAsCharacter = Cast<ACharacter>(Actor);
	if (actorAsCharacter)
	{

		FVector LaunchDirection = FVector::UpVector + FMath::VRandCone(FVector::UpVector, 99.f);

		FVector LaunchImpulse = LaunchDirection.GetSafeNormal() * Speed;
		actorAsCharacter->LaunchCharacter(LaunchImpulse, true, true);
	}
}
