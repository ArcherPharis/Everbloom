// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Components/WidgetSwitcher.h"
#include "AbilityFlowerItem.h"
#include "PlayerStatsWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/ListView.h"

void UInGameUI::SwitchToFloriology()
{
	WidgetSwitcher->SetActiveWidget(FloriologyMenu);
}

void UInGameUI::NewAbilityFlowerGiven(UAbilityFlowerItem* Flower)
{
	UE_LOG(LogTemp, Warning, TEXT("getting to the UI"));
	AbilityFlowerList->AddItem(Flower);
	AbilityFlowerList->RequestRefresh();
}

void UInGameUI::ToggleMenu(bool ShouldToggle, float health, float maxHealth, float strength, float mag, float def, float res, float wepAug)
{
	if (ShouldToggle)
	{
		WidgetSwitcher->SetActiveWidget(MenuCanvas);
	}
	else
	{
		WidgetSwitcher->SetActiveWidget(MainCanvas);

	}
	StatsWidget->SetAllStatTexts(FString::FromInt(health),
		FString::FromInt(maxHealth), 
		FString::FromInt(strength), 
		FString::FromInt(mag), 
		FString::FromInt(def), 
		FString::FromInt(res),
		FString::FromInt(wepAug));
}

