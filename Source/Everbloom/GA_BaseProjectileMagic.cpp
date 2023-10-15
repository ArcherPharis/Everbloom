// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BaseProjectileMagic.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "BaseProjectile.h"
#include "BaseCharacter.h"
#include "Emilia.h"

void UGA_BaseProjectileMagic::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

	if (!CheckCost(Handle, ActorInfo))
		return;

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	Emilia = Cast<AEmilia>(GetAvatarAsCharacter());
	Emilia->StartAim();
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


}

void UGA_BaseProjectileMagic::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	Emilia->EndAim();
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
	FTransform SocketTransform = MeshComponent->GetSocketTransform(FName("hand_r"));
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
	
}

void UGA_BaseProjectileMagic::UpdateFireStatus()
{
	bCanFire = true;
}
