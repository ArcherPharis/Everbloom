// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Evade.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "BaseCharacter.h"
#include "GameFramework./CharacterMovementComponent.h"




void UGA_Evade::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//BrakingDeccelerationWalking and GroundFriction to 0

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UAbilityTask_PlayMontageAndWait* EvadeMontagePlay = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, EvadeMontage);
	if (EvadeMontagePlay)
	{
		EvadeMontagePlay->OnBlendOut.AddDynamic(this, &UGA_Evade::MontageEnded);
		EvadeMontagePlay->OnCancelled.AddDynamic(this, &UGA_Evade::MontageEnded);
		EvadeMontagePlay->OnInterrupted.AddDynamic(this, &UGA_Evade::MontageEnded);
		EvadeMontagePlay->OnCompleted.AddDynamic(this, &UGA_Evade::MontageEnded);
		EvadeMontagePlay->ReadyForActivation();
	}

	UAbilityTask_WaitGameplayEvent* EndMoveEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, EndMovementTag, nullptr, false, false);
	if (EndMoveEvent)
	{
		EndMoveEvent->EventReceived.AddDynamic(this, &UGA_Evade::EndMovement);
		EndMoveEvent->ReadyForActivation();
	}

	ACharacter* Chara = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MoveComp = Chara->GetCharacterMovement();
	OriginalGroundFriction = MoveComp->GroundFriction;
	FVector EvadeDirection;
	if (MoveComp->GetLastInputVector() == FVector::ZeroVector)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Chara->GetController());
		FRotator ControlRotation = PlayerController->GetControlRotation();
		EvadeDirection = ControlRotation.Vector();
	}
	else
	{
		EvadeDirection = MoveComp->GetLastInputVector();
	}
	FRotator EvadeRotation = FRotator(0, EvadeDirection.Rotation().Yaw, 0);
	MoveComp->GroundFriction = 0;
	float Speed = EvadeSpeed;
	if (MoveComp->IsFalling())
	{
		Speed /= 1.2f;
	}
	FVector EvadeVelocity = EvadeDirection.GetSafeNormal() * Speed;
	MoveComp->Velocity = EvadeVelocity;
	Chara->SetActorRotation(EvadeRotation);
}

void UGA_Evade::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	ACharacter* Chara = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MoveComp = Chara->GetCharacterMovement();
	MoveComp->GroundFriction = OriginalGroundFriction;
	if(!MoveComp->IsFalling())
	MoveComp->StopMovementImmediately();


}

void UGA_Evade::EndMovement(FGameplayEventData Payload)
{

	ACharacter* Chara = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MoveComp = Chara->GetCharacterMovement();
	if (!MoveComp->IsFalling())
	{
		K2_EndAbility();

	}
	else
	{
		UAbilityTask_WaitGameplayEvent* EndMoveEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, LandingTag, nullptr, false, false);
		if (EndMoveEvent)
		{
			EndMoveEvent->EventReceived.AddDynamic(this, &UGA_Evade::Landed);
			EndMoveEvent->ReadyForActivation();
		}
		//GetWorld()->GetTimerManager().SetTimer(CanEvadeAgainTimer, this, &UGA_Evade::AllowForEvasion, 0.3f, false);
	}

}

void UGA_Evade::Landed(FGameplayEventData Payload)
{
	K2_EndAbility();
}

void UGA_Evade::MontageEnded()
{
	ACharacter* Chara = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MoveComp = Chara->GetCharacterMovement();
	if (MoveComp->IsFalling())
		return;
	K2_EndAbility();
}

void UGA_Evade::AllowForEvasion()
{
	ACharacter* Chara = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	Chara->GetMesh()->GetAnimInstance()->Montage_Play(RecoveryMontage);
	GetWorld()->GetTimerManager().ClearTimer(CanEvadeAgainTimer);
	Chara->GetCharacterMovement()->AddImpulse(GetAvatarActorFromActorInfo()->GetActorUpVector() * 400, true);
	K2_EndAbility();
}
