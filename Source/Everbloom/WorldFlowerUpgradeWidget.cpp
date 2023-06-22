// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldFlowerUpgradeWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UWorldFlowerUpgradeWidget::SetUpgradeIcon(UTexture2D* Texture)
{
	Icon->SetBrushFromTexture(Texture);
}

void UWorldFlowerUpgradeWidget::SetUpgradeNameText(FText NewText)
{
	UpgradeNameText->SetText(NewText);
}
