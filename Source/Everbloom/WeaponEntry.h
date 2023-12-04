// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "WeaponEntry.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UWeaponEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
private:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);

	UPROPERTY(meta=(BindWidget))
	class UImage* SwordIcon;

	UPROPERTY(meta = (BindWidget))
	class UButton* WeaponButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* WeaponText;

	
};
