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
		EvadeMontagePlay->OnBlendOut.AddDynamic(this, &UGA_Evade::K2_EndAbility);
		EvadeMontagePlay->OnCancelled.AddDynamic(this, &UGA_Evade::K2_EndAbility);
		EvadeMontagePlay->OnInterrupted.AddDynamic(this, &UGA_Evade::K2_EndAbility);
		EvadeMontagePlay->OnCompleted.AddDynamic(this, &UGA_Evade::K2_EndAbility);
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
	FVector EvadeVelocity = EvadeDirection.GetSafeNormal() * EvadeSpeed;
	MoveComp->Velocity = EvadeVelocity;
	Chara->SetActorRotation(EvadeRotation);
}

void UGA_Evade::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	ACharacter* Chara = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	UCharacterMovementComponent* MoveComp = Chara->GetCharacterMovement();
	MoveComp->GroundFriction = OriginalGroundFriction;
	MoveComp->StopMovementImmediately();


}

void UGA_Evade::EndMovement(FGameplayEventData Payload)
{

	K2_EndAbility();
}
