// Fill out your copyright notice in the Description page of Project Settings.


#include "FloriologyCraftingWidget.h"
#include "Components/Image.h"
#include "AbilityFlowerItem.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "FloriologyCraftingWidget.h"
#include "AbilityNodeEntry.h"

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

void UFloriologyCraftingWidget::EnableValidCombinationButton(TSubclassOf<class UEBGameplayAbilityBase> ValidAbility)
{
	ToggleCombinationButton(true);
	HeldAbility = ValidAbility;

}

void UFloriologyCraftingWidget::DisableValidCombinationButton()
{
	ToggleCombinationButton(false);
	HeldAbility = nullptr;
}

void UFloriologyCraftingWidget::ToggleCombinationButton(bool bToggle)
{
	MakeFlowerButton->SetIsEnabled(bToggle);
}

void UFloriologyCraftingWidget::AddToNodeEntryList(UAbilityFlowerItem* Item)
{
	//NodeEntryList->ClearListItems();
	NodeEntryList->AddItem(Item);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([this, Item]() {
		
		UAbilityNodeEntry* Entry =  Cast<UAbilityNodeEntry>(NodeEntryList->GetEntryWidgetFromItem(Item));
		if (Entry)
		{
			Entry->OnNodePressed.AddDynamic(this, &UFloriologyCraftingWidget::ProcessFlowerItem);
		}
		});

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.1f, false);
}

void UFloriologyCraftingWidget::ClearNodes()
{
	
	TArray<UUserWidget*> Entries = NodeEntryList->GetDisplayedEntryWidgets();

	for (UUserWidget* Entry : Entries)
	{
		UAbilityNodeEntry* Node = Cast<UAbilityNodeEntry>(Entry);
		if (Node)
		{
			Node->OnNodePressed.RemoveDynamic(this, &UFloriologyCraftingWidget::ProcessFlowerItem);
		}
	}
	NodeEntryList->ClearListItems();
}


void UFloriologyCraftingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	MakeFlowerButton->OnClicked.AddDynamic(this, &UFloriologyCraftingWidget::AbilityButtonPressed);
	MakeFlowerButton->SetIsEnabled(false);

}

void UFloriologyCraftingWidget::ProcessFlowerItem(UAbilityFlowerItem* FlowerItem)
{
	OnCreationWidget.Broadcast(FlowerItem);
}

void UFloriologyCraftingWidget::AbilityButtonPressed()
{
	if (HeldAbility)
	{
		OnAddAbility.Broadcast(HeldAbility);

	}
}
