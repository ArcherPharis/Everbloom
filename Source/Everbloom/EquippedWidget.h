// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquippedWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UEquippedWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void ChangeWeaponDisplayed(UTexture2D* NewImage, FText NewName);

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponChangedEvent();

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* EquippedIcon;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EquippedName;

private:

	
};
