// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UBossHealthBar : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void SetHealthPercent(float NewValue, float MaxHealth, float OldHealth);
	void SetBossName(FText Name);


private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* BossNameText;
	
};
