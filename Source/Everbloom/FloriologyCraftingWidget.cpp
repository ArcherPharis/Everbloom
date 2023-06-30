// Fill out your copyright notice in the Description page of Project Settings.


#include "FloriologyCraftingWidget.h"
#include "Components/Image.h"
#include "AbilityFlowerItem.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"

void UFloriologyCraftingWidget::SetFlowerOneImage(UTexture2D* FlowerIcon, FText FlowerName)
{
	FlowerOneImage->SetVisibility(ESlateVisibility::Visible);
	MasterNodeImage->SetVisibility(ESlateVisibility::Visible);
	FlowerOneImage->SetBrushFromTexture(FlowerIcon);
	FlowerOneName->SetText(FlowerName);
}

void UFloriologyCraftingWidget::SetFlowerTwoImage(UTexture2D* FlowerIcon)
{
	//FlowerTwoImage->SetBrushFromTexture(FlowerIcon);

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

void UFloriologyCraftingWidget::AddToNodeEntryList(UAbilityFlowerItem* Item)
{
	//NodeEntryList->ClearListItems();
	NodeEntryList->AddItem(Item);
}

void UFloriologyCraftingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MakeFlowerButton->SetIsEnabled(false);
}
