// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityInputModifier.h"

FInputActionValue UAbilityInputModifier::ModifyRaw_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue CurrentValue, float DeltaTime)
{
	return CurrentValue.Get<FVector>() * static_cast<int32>(InputID);
}
