// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseItemObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class EVERBLOOM_API UBaseItemObject : public UObject
{
	GENERATED_BODY()

public:
	FText GetItemName() const { return ItemName; }
	UTexture2D* GetItemIcon() const { return ItemIcon; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (MultiLine = true))
	FText ItemName;

	UPROPERTY(EditDefaultsOnly, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	UTexture2D* ItemIcon;
	
};
