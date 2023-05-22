// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GA_ThunderboltTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API AGA_ThunderboltTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AGA_ThunderboltTargetActor();

private:
	virtual void StartTargeting(UGameplayAbility* Ability);

	virtual void ConfirmTargetingAndContinue();

	virtual void Tick(float deltaTime) override;

	UPROPERTY()
	class USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "TargetActor")
	class USphereComponent* TargetArea;
	
};
