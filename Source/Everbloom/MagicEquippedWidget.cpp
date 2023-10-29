// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicEquippedWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMagicEquippedWidget::SetWidgetsVisible()
{
	EquippedIcon->SetVisibility(ESlateVisibility::Visible);
	EquippedName->SetVisibility(ESlateVisibility::Visible);
}
