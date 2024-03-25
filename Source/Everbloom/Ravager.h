// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "Ravager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDied);

/**
 * 
 */
UCLASS()
class EVERBLOOM_API ARavager : public ABaseEnemy
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, Category = "Ravager")
	class ARavagerCampfire* Campfire;

	virtual void HandleCharacterHealth(float NewValue, float MaxHealth, float OldHealth) override;
	
};
