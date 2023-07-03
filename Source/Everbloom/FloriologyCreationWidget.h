// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FloriologyCreationWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UFloriologyCreationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetCreationBox(class UAbilityFlowerItem* FlowerItem, TSubclassOf<class UEBGameplayAbilityBase> Ability);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* RequiredItemText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SpellNameText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DescriptionText;

	UPROPERTY(meta = (BindWidget))
	class UImage* SpellIcon;
	
};
