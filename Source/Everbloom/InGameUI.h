// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void SwitchToFloriology();

	UFUNCTION()
	void NewAbilityFlowerGiven(class UAbilityFlowerItem* Flower);

	UFUNCTION()
	void ToggleMenu(bool ShouldToggle, float health, float maxHealth, float strength, float mag, float def, float res, float wepAug);


private:

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* MainCanvas;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* FloriologyMenu;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* MenuCanvas;

	UPROPERTY(meta = (BindWidget))
	class UListView* AbilityFlowerList;

	UPROPERTY(meta = (BindWidget))
	class UPlayerStatsWidget* StatsWidget;
	
};
