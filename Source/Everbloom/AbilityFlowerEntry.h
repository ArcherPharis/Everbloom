// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "AbilityFlowerEntry.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UAbilityFlowerEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	class UImage* FlowerIcon;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FlowerName;
	
};
