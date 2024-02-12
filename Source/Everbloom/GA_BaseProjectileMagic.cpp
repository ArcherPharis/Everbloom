// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BaseProjectileMagic.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "BaseProjectile.h"
#include "BaseCharacter.h"
#include "Emilia.h"
#include "EBPlayerController.h"
#include "InGameUI.h"

void UGA_BaseProjectileMagic::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	if (!CheckCost(Handle, ActorInfo))
		return;

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	Emilia = Cast<AEmilia>(GetAvatarAsCharacter());
	Emilia->StartAim();
	AEBPlayerController* PlayerController = Cast<AEBPlayerController>(Emilia->GetOwner());
	Reticle = PlayerController->PCCreateWidget(ReticleClass);
	UAbilityTask_WaitGameplayEvent* FireEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, PlayerInputFireTag, nullptr, false, false);
	if (FireEvent)
	{
		FireEvent->EventReceived.AddDynamic(this, &UGA_BaseProjectileMagic::DetermineFiring);
		FireEvent->ReadyForActivation();
	}
	GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &UGA_BaseProjectileMagic::UpdateFireStatus, 0.2f, false);


	UAbilityTask_WaitGameplayEvent* EndEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EndAbilityTag, nullptr, false, false);
	if (EndEvent)
	{
		EndEvent->EventReceived.AddDynamic(this, &UGA_BaseProjectileMagic::EndFromInputRelease);
		EndEvent->ReadyForActivation();
	}

	UAbilityTask_PlayMontageAndWait* AimMontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AimMontage);
	if (AimMontagePlay)
	{
		AimMontagePlay->OnBlendOut.AddDynamic(this, &UGA_BaseProjectileMagic::MontageFinished);
		AimMontagePlay->OnCancelled.AddDynamic(this, &UGA_BaseProjectileMagic::MontageFinished);
		AimMontagePlay->OnInterrupted.AddDynamic(this, &UGA_BaseProjectileMagic::MontageFinished);
		AimMontagePlay->OnCompleted.AddDynamic(this, &UGA_BaseProjectileMagic::MontageFinished);
		AimMontagePlay->ReadyForActivation();
	}



}

void UGA_BaseProjectileMagic::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	Emilia->EndAim();
	if (Reticle)
	{
		Reticle->RemoveFromParent();
	}
}

void UGA_BaseProjectileMagic::DetermineFiring(FGameplayEventData Payload)
{
	if (!CheckCost(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo()))
	{
		K2_EndAbility();
		return;
	}
		

	if (!bCanFire) return;
	K2_CommitAbility();
	bCanFire = false;
	GetWorld()->GetTimerManager().SetTimer(ShootHandle, this, &UGA_BaseProjectileMagic::UpdateFireStatus, 1/FireRate, false);

	ABaseProjectile* Projectile = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass);
	Projectile->SetCaster(Emilia);
	USkeletalMeshComponent* MeshComponent = Emilia->GetMesh();
	FTransform SocketTransform = MeshComponent->GetSocketTransform(FName("cup_r"));
	Projectile->SetActorLocation(SocketTransform.GetLocation());
	FVector CameraDirection = Emilia->GetControlRotation().Vector();
	Projectile->SetActorRotation(CameraDirection.Rotation());
	Projectile->SetProjectileVelocity(CameraDirection, Effect);
	FireEvent();
}

void UGA_BaseProjectileMagic::EndFromInputRelease(FGameplayEventData Payload)
{
	K2_EndAbility();
}

void UGA_BaseProjectileMagic::MontageFinished()
{
	K2_EndAbility();
}

void UGA_BaseProjectileMagic::UpdateFireStatus()
{
	bCanFire = true;
}
