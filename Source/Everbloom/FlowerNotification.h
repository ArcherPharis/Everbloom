// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FlowerNotification.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UFlowerNotification : public UUserWidget
{
	GENERATED_BODY()

public:
	void PopulateNotificationFields(UTexture2D* Image, FText Name, FText Amount);

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* ItemImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemNameText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DescriptionText;
	
};
