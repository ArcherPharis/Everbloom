// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowerNotification.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UFlowerNotification::PopulateNotificationFields(UTexture2D* Image, FText Name, FText Description)
{
	ItemImage->SetBrushFromTexture(Image);
	ItemNameText->SetText(Name);
	DescriptionText->SetText(Description);

}
