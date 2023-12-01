// Fill out your copyright notice in the Description page of Project Settings.


#include "BossHealthBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBossHealthBar::SetHealthPercent(float Current, float Max)
{
	HealthBar->SetPercent(Current / Max);
}

void UBossHealthBar::SetBossName(FText Name)
{
	BossNameText->SetText(Name);
}
