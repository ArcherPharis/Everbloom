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

public:
	void SetStrengthText(FString Text);
	void SetHealthText(FString Text);
	void SetMaxHealthText(FString Text);
	void SetMagicText(FString Text);
	void SetDefenseText(FString Text);
	void SetResistanceText(FString Text);
	void SetAllStatTexts(FString HP, FString MaxHP, FString Str, FString Mag, FString Def, FString Res, FString StrAug);



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
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MagText;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* MagProgressBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DefenseText;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* DefenseProgressBar;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ResistanceText;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* ResistanceProgressBar;
	
};
