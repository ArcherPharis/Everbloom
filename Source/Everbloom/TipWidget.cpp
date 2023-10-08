// Fill out your copyright notice in the Description page of Project Settings.


#include "TipWidget.h"
#include "Components/TextBlock.h"

void UTipWidget::SetTipText(FText NewText)
{
	Text->SetText(NewText);
}
