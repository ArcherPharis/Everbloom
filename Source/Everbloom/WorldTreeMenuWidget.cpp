// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldTreeMenuWidget.h"
#include "Components/TextBlock.h"
#include "WorldFlowerUpgradeWidget.h"

void UWorldTreeMenuWidget::SetLifedewAmount(int Amount)
{
	NumOfPlayerLifedew->SetText(FText::FromString(FString::FromInt(Amount)));
}

void UWorldTreeMenuWidget::SetWorldFlowerText(FName FlowerName)
{
	CurrentWorldFlowerText->SetText(FText::FromName(FlowerName));
}

void UWorldTreeMenuWidget::SetSpecialityWidgetParams(FText Name, UTexture2D* IconImage)
{
	SpecialityUpgradeWidget->SetUpgradeIcon(IconImage);
	SpecialityUpgradeWidget->SetUpgradeNameText(Name);
}
