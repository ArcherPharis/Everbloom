// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Components/WidgetSwitcher.h"
#include "AbilityFlower.h"
#include "Components/CanvasPanel.h"
#include "Components/ListView.h"

void UInGameUI::SwitchToFloriology()
{
	WidgetSwitcher->SetActiveWidget(FloriologyMenu);
}

void UInGameUI::NewAbilityFlowerGiven(AAbilityFlower* Flower)
{
	UE_LOG(LogTemp, Warning, TEXT("getting to the UI"));
	AbilityFlowerList->AddItem(Flower);
	AbilityFlowerList->RequestRefresh();
}
