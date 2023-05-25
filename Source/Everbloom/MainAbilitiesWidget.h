// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainAbilitiesWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UMainAbilitiesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void AddMainAbility(class UEBGameplayAbilityBase* Ability, class AEmilia* Player);

private:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* AbilityEntryBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UMainAbilityEntry> MainAbilityEntryWidget;
	
};
