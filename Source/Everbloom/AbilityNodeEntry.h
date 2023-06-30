// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "AbilityNodeEntry.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UAbilityNodeEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	class UImage* NodeImage;

	UPROPERTY()
	class UAbilityFlowerItem* SecondFlower;
	
};
