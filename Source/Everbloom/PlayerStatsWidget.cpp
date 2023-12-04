// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatsWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/ListView.h"
#include "Weapon.h"

void UPlayerStatsWidget::SetStrengthText(FString Text)
{
	StrengthText->SetText(FText::FromString(Text));
}

void UPlayerStatsWidget::SetHealthText(FString Text)
{
	CurrentHealthText->SetText(FText::FromString(Text));
}

void UPlayerStatsWidget::SetMaxHealthText(FString Text)
{
	MaxHealthText->SetText(FText::FromString(Text));
}

void UPlayerStatsWidget::SetMagicText(FString Text)
{
	MagText->SetText(FText::FromString(Text));
}

void UPlayerStatsWidget::SetDefenseText(FString Text)
{
	DefenseText->SetText(FText::FromString(Text));
}

void UPlayerStatsWidget::SetResistanceText(FString Text)
{
	ResistanceText->SetText(FText::FromString(Text));
}


void UPlayerStatsWidget::SetAllStatTexts(FString HP, FString MaxHP, FString Str, FString Mag, FString Def, FString Res, FString StrAug)
{
	SetHealthText(HP);
	SetMaxHealthText(MaxHP);
	SetStrengthText(Str);
	SetMagicText(Mag);
	SetDefenseText(Def);
	SetResistanceText(Res);
}

void UPlayerStatsWidget::SetPercentageBars(float HP, float Str, float Mag, float Def, float Res)
{
	HealthProgressBar->SetPercent(HP / MaxHealthAmount);
	StrengthProgressBar->SetPercent(Str / MaxStatAmount);
	MagProgressBar->SetPercent(Mag / MaxStatAmount);
	DefenseProgressBar->SetPercent(Def / MaxStatAmount);
	ResistanceProgressBar->SetPercent(Res / MaxStatAmount);

}

void UPlayerStatsWidget::GiveWeaponToList(AWeapon* NewWep)
{
	WeaponListView->AddItem(NewWep);
}
