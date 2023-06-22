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

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NumOfPlayerLifedew;
	
};
