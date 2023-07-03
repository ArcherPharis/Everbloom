// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityFlowerEntry.h"
#include "AbilityFlowerItem.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UAbilityFlowerEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	UAbilityFlowerItem* Flower = GetListItem<UAbilityFlowerItem>();
	FlowerIcon->SetBrushFromTexture(Flower->GetItemIcon());
	FlowerName->SetText(Flower->GetItemName());
	FlowerButton->OnClicked.AddDynamic(this, &UAbilityFlowerEntry::FlowerButtonPressed);
}

void UAbilityFlowerEntry::FlowerButtonPressed()
{
	UAbilityFlowerItem* Item = GetListItem<UAbilityFlowerItem>();
	OnEntryClicked.Broadcast(Item);
	//FlowerButton->SetIsEnabled(false);
}
