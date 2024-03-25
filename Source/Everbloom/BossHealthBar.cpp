// Fill out your copyright notice in the Description page of Project Settings.


#include "BossHealthBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBossHealthBar::SetHealthPercent(float NewValue, float MaxHealth, float OldHealth)
{
	HealthBar->SetPercent(NewValue / MaxHealth);
}

void UBossHealthBar::SetBossName(FText Name)
{
	BossNameText->SetText(Name);
}
