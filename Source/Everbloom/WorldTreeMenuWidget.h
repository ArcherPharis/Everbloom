// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorldTreeMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UWorldTreeMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetLifedewAmount(int Amount);
	void SetWorldFlowerText(FName FlowerName);
	void SetSpecialityWidgetParams(FText Name, UTexture2D* IconImage);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NumOfPlayerLifedew;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentWorldFlowerText;

	UPROPERTY(meta = (BindWidget))
	class UWorldFlowerUpgradeWidget* HealthUpgradeWidget;

	UPROPERTY(meta = (BindWidget))
	class UWorldFlowerUpgradeWidget* SpecialityUpgradeWidget;
};
