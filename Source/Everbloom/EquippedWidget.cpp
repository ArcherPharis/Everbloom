// Fill out your copyright notice in the Description page of Project Settings.


#include "EquippedWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UEquippedWidget::ChangeWeaponDisplayed(UTexture2D* NewImage, FText NewName)
{
	EquippedIcon->SetBrushFromTexture(NewImage);
	EquippedName->SetText(NewName);
	OnWeaponChangedEvent();
}
