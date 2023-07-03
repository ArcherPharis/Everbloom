// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityNodeEntry.h"
#include "Components/Button.h"
#include "AbilityFlowerItem.h"
#include "FloriologyCraftingWidget.h"
#include "Components/ListView.h"

void UAbilityNodeEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	NodeButton->OnPressed.AddDynamic(this, &UAbilityNodeEntry::OnButtonPressed);
}

void UAbilityNodeEntry::OnButtonPressed()
{
	UAbilityFlowerItem* FlowerItem =  GetListItem<UAbilityFlowerItem>();
	
	if (FlowerItem)
	{
		OnNodePressed.Broadcast(FlowerItem);
	}
}
