// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Movement.h"
#include "Emilia.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Camera/CameraComponent.h"


void UGA_Movement::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAbilityTask_WaitGameplayEvent* XMovementEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, XMovementTag, nullptr, false, false);
	if (XMovementEvent)
	{
		XMovementEvent->EventReceived.AddDynamic(this, &UGA_Movement::MoveCharacterX);
		XMovementEvent->ReadyForActivation();
	}
	UAbilityTask_WaitGameplayEvent* YMovementEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, YMovementTag, nullptr, false, false);
	if (YMovementEvent)
	{
		YMovementEvent->EventReceived.AddDynamic(this, &UGA_Movement::MoveCharacterY);
		YMovementEvent->ReadyForActivation();
	}
	Emilia = Cast<AEmilia>(GetAvatarAsCharacter());
}

void UGA_Movement::MoveCharacterX(FGameplayEventData Payload)
{
	GetAvatarAsCharacter()->AddMovementInput(Emilia->GetCameraComponent()->GetRightVector(), Payload.EventMagnitude);
	
}

void UGA_Movement::MoveCharacterY(FGameplayEventData Payload)
{
	GetAvatarAsCharacter()->AddMovementInput(FVector(Emilia->GetCameraComponent()->GetForwardVector().X, Emilia->GetCameraComponent()->GetForwardVector().Y, 0).GetSafeNormal(), Payload.EventMagnitude);
	K2_EndAbility();

}

void UGA_Movement::MoveCharacter(FVector2D Input, FVector CameraForwardVector, FVector CameraRightVector)
{
}
