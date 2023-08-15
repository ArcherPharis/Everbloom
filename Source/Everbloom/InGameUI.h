// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void SwitchToFloriology();

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeHealthBarColor(float CurrentPercent);

	void AddNewMainAbility(class UEBGameplayAbilityBase* Ability, class AEmilia* Player);

	UFUNCTION(BlueprintPure)
	class UProgressBar* GetHealthBar() const { return HealthBar; }

	UFUNCTION()
	void SetHealthBar(float CurrentValue, float MaxValue);

	UFUNCTION()
	void NewAbilityFlowerGiven(class UAbilityFlowerItem* Flower);

	UFUNCTION()
	void ToggleMenu(bool ShouldToggle, float health, float maxHealth, float strength, float mag, float def, float res, float wepAug);

	UFUNCTION()
	void EnableCreationWidget(UAbilityFlowerItem* FlowerItem);

protected:
	virtual void NativeConstruct() override;

private:

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UMainAbilitiesWidget* MainAbilities;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* MainCanvas;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* FloriologyMenu;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* MenuCanvas;

	UPROPERTY(meta = (BindWidget))
	class UListView* AbilityFlowerList;

	UPROPERTY(meta = (BindWidget))
	class UPlayerStatsWidget* StatsWidget;
	UPROPERTY(meta = (BindWidget))
	class UFloriologyCraftingWidget* CraftingWidget;

	UPROPERTY()
	class UAbilityFlowerItem* FlowerOne;
	UPROPERTY()
	class UAbilityFlowerItem* FlowerTwo;

	UFUNCTION()
	void HandleFlowerFromEntry(UAbilityFlowerItem* FlowerGiven);

	UFUNCTION()
	void SpawnUpgradeNodes(UAbilityFlowerItem* FlowerGiven);

	UFUNCTION()
	void GiveAbilityToPlayer(TSubclassOf<class UEBGameplayAbilityBase> Ability);

	UPROPERTY()
	class AEverbloomGameModeBase* Gamemode;

	void HandleNewFlowerEntry(UUserWidget& UserWidget);
	
};
