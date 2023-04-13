// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityFlowerEntry.h"
#include "AbilityFlower.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UAbilityFlowerEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	AAbilityFlower* Flower = GetListItem<AAbilityFlower>();
	FlowerIcon->SetBrushFromTexture(Flower->GetItemIcon());
	FlowerName->SetText(Flower->GetItemName());
}
