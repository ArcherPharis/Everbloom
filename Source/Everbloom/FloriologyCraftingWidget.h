// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FloriologyCraftingWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UFloriologyCraftingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetFlowerOneImage(UTexture2D* FlowerIcon);
	void SetFlowerTwoImage(UTexture2D* FlowerIcon);


protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* FlowerOneImage;
	UPROPERTY(meta = (BindWidget))
	UImage* FlowerTwoImage;

	UPROPERTY(meta = (BindWidget))
	class UButton* MakeFlowerButton;
	
};
