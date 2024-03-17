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
	void SetManaBar(float CurrentValue, float MaxValue);

	UFUNCTION()
	void NewAbilityFlowerGiven(class UAbilityFlowerItem* Flower);

	UFUNCTION()
	void ToggleMenu(bool ShouldToggle, float health, float maxHealth, float strength, float mag, float def, float res, float wepAug);

	UFUNCTION()
	void EnableCreationWidget(UAbilityFlowerItem* FlowerItem);

	UFUNCTION()
	void CreateNewTip(FText TextToGiveTip);

	UFUNCTION()
	void AddToFlowerNotificationBox(UAbilityFlowerItem* Flower);

	UFUNCTION()
	void AddNewWeaponToStats(class AWeapon* Weapon);

	UFUNCTION()
	void SetTipText(FText Message, bool Show);

	UFUNCTION()
	void SetGemIcons(UTexture2D* Icon, int IndexAt);

	void ChangeCurrentEquippedWeapon(UTexture2D* Image, FText Name);

	void ChangeCurrentEquippedMagic(UTexture2D* Image, FText Name);

	UFUNCTION()
	void SetDewfruitText(float NewAmount);

	UFUNCTION()
	void SetLifedewAmount(int NewAmount);

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
	UProgressBar* ManaBar;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* MainCanvas;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* FloriologyMenu;
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* MenuCanvas;

	UPROPERTY(meta = (BindWidget))
	class UListView* AbilityFlowerList;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* TipBox;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* FlowerNotificationBox;

	UPROPERTY(meta = (BindWidget))
	class UPlayerStatsWidget* StatsWidget;
	UPROPERTY(meta = (BindWidget))
	class UFloriologyCraftingWidget* CraftingWidget;
	UPROPERTY(meta = (BindWidget))
	class UEquippedWidget* EquippedWeaponWidget;
	UPROPERTY(meta = (BindWidget))
	class UMagicEquippedWidget* MagicEquippedWeaponWidget;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DewfruitText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* LifedewText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TipText;

	UPROPERTY(meta = (BindWidget))
	class UImage* GemIconOne;
	UPROPERTY(meta = (BindWidget))
	UImage* GemIconTwo;
	UPROPERTY(meta = (BindWidget))
	UImage* GemIconThree;

	UPROPERTY(EditDefaultsOnly, Category = "Tips")
	TSubclassOf<class UTipWidget> TipWidgetClass;

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

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UFlowerNotification> FlowerNotificationWidgetClass;

	bool bNoMagicYet = true;
	
};
