// Fill out your copyright notice in the Description page of Project Settings.


#include "FloriologyCraftingWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"

void UFloriologyCraftingWidget::SetFlowerOneImage(UTexture2D* FlowerIcon)
{
	FlowerOneImage->SetBrushFromTexture(FlowerIcon);
}

void UFloriologyCraftingWidget::SetFlowerTwoImage(UTexture2D* FlowerIcon)
{
	FlowerTwoImage->SetBrushFromTexture(FlowerIcon);

}

void UFloriologyCraftingWidget::EnableValidCombinationButton(TSubclassOf<class UGameplayAbility> ValidAbility)
{
	ToggleCombinationButton(true);
	HeldAbility = ValidAbility;

}

void UFloriologyCraftingWidget::ToggleCombinationButton(bool bToggle)
{
	MakeFlowerButton->SetIsEnabled(bToggle);
}

void UFloriologyCraftingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MakeFlowerButton->SetIsEnabled(false);
}
