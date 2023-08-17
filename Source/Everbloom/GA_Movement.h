// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBGameplayAbilityBase.h"
#include "GA_Movement.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UGA_Movement : public UEBGameplayAbilityBase
{
	GENERATED_BODY()

private:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FGameplayTag XMovementTag;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FGameplayTag YMovementTag;

	UFUNCTION()
	void MoveCharacterX(FGameplayEventData Payload);
	UFUNCTION()
	void MoveCharacterY(FGameplayEventData Payload);

	class AEmilia* Emilia;

public:
	void MoveCharacter(FVector2D Input, FVector CameraForwardVector, FVector CameraRightVector);
	
};
