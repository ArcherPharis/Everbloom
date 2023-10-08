// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TipWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UTipWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetTipText(FText NewText);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text;
	
};
