// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldTreeMenuWidget.h"
#include "Components/TextBlock.h"

void UWorldTreeMenuWidget::SetLifedewAmount(int Amount)
{
	NumOfPlayerLifedew->SetText(FText::FromString(FString::FromInt(Amount)));
}
