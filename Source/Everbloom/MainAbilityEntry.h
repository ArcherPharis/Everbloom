// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffect.h"
#include "MainAbilityEntry.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UMainAbilityEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitAbilityIcon(UTexture2D* IconToSet, class UEBGameplayAbilityBase* AbilityForEntry, class AEmilia* Emilia);

	void SetAbilityCooldownBar(float CurrentDuration, float Duration);

	UEBGameplayAbilityBase* GetAbility() const { return Ability; }

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* AbilityIcon;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* CooldownBar;

	UPROPERTY()
	class UEBGameplayAbilityBase* Ability;

	UFUNCTION()
	void StartCooldownBar();

	class UEBAbilitySystemComponent* AbilitySystemComponent;
	FGameplayAbilitySpec* AbilitySpec;
	FGameplayAbilitySpecHandle AbilitySpecHandle;

	class AActor* Chata;

	bool bIsCoolingDown = false;
	
};
