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
	void SetPercentageBars(float HP, float Str, float Mag, float Def, float Res);
	void GiveWeaponToList(class AWeapon* NewWep);

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

	UPROPERTY(meta = (BindWidget))
	class UListView* WeaponListView;

	float MaxStatAmount = 300.f;
	float MaxHealthAmount = 1000.f;
	
};
