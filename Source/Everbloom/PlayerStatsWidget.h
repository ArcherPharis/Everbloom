// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatsWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UPlayerStatsWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentHealthText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MaxHealthText;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthProgressBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StrengthText;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* StrengthProgressBar;
	
};
