// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_ProjectileMagic.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "BaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework./CharacterMovementComponent.h"
#include "BaseCharacter.h"
#include "Emilia.h"

void UGA_ProjectileMagic::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* CastMontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, CastingMontage);
	if (CastMontagePlay)
	{
		CastMontagePlay->OnBlendOut.AddDynamic(this, &UGA_ProjectileMagic::MontageFinished);
		CastMontagePlay->OnCancelled.AddDynamic(this, &UGA_ProjectileMagic::MontageFinished);
		CastMontagePlay->OnInterrupted.AddDynamic(this, &UGA_ProjectileMagic::MontageFinished);
		CastMontagePlay->OnCompleted.AddDynamic(this, &UGA_ProjectileMagic::MontageFinished);
		CastMontagePlay->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* CastEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, CastMagicTag, nullptr, false, false);
	if (CastEvent)
	{
		CastEvent->EventReceived.AddDynamic(this, &UGA_ProjectileMagic::CastProjectile);
		CastEvent->ReadyForActivation();
	}
	ABaseCharacter* CastingActor = GetAvatarAsCharacter();
	CastingActor->RotateTowardsLockedTarget();

	if (CastingActor->GetCharacterMovement()->IsFalling())
	{
		CastingActor->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorUpVector() * 300.f, true);
	}
}

void UGA_ProjectileMagic::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UGA_ProjectileMagic::MontageFinished()
{
	K2_EndAbility();
}

void UGA_ProjectileMagic::CastProjectile(FGameplayEventData Payload)
{
	ABaseProjectile* Projectile = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass);
	Projectile->SetCaster(GetAvatarActorFromActorInfo());
	ABaseCharacter* CastingActor = GetAvatarAsCharacter();
	USkeletalMeshComponent* MeshComponent = CastingActor->GetMesh();
	FTransform SocketTransform = MeshComponent->GetSocketTransform(FName("hand_r"));
	Projectile->SetActorLocation(SocketTransform.GetLocation());
	FVector CameraDirection = CastingActor->GetControlRotation().Vector();
	FVector ForwardDirection = CastingActor->GetActorForwardVector();
	float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(CameraDirection, ForwardDirection)));
	if (FMath::Abs(Angle) > 90.0f)
	{
		CameraDirection = ForwardDirection;
	}
	Projectile->SetActorRotation(CameraDirection.Rotation());
	Projectile->SetProjectileVelocity(CameraDirection, EffectToApply);

	if (AEmilia* Em = Cast<AEmilia>(CastingActor))
	{
		AActor* Targ = Em->GetLockedOnTarget();
		if (Targ)
		Projectile->SetHomingTarget(Targ, EffectToApply);
	}
	
	if (bIsRapidFire)
	{
		K2_EndAbility();
	}
	
}
