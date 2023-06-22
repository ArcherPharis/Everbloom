// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorldFlowerUpgradeWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UWorldFlowerUpgradeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetUpgradeIcon(UTexture2D* Texture);
	void SetUpgradeNameText(FText NewText);

private:
	UPROPERTY(meta=(BindWidget))
	class UImage* Icon;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* UpgradeNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* UpgradeDescriptionText;

	UPROPERTY(meta = (BindWidget))
	class UImage* CostIcon;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CostText;
	
};
