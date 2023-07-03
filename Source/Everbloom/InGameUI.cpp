// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "Components/WidgetSwitcher.h"
#include "Components/ProgressBar.h"
#include "AbilityFlowerItem.h"
#include "PlayerStatsWidget.h"
#include "AbilityFlowerEntry.h"
#include "EBGameplayAbilityBase.h"
#include "EverbloomGameModeBase.h"
#include "FloriologyCraftingWidget.h"
#include "FloriologyRecipes.h"
#include "Kismet/GameplayStatics.h"
#include "FloriologyCreationWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/ListView.h"
#include "MainAbilitiesWidget.h"

void UInGameUI::SwitchToFloriology()
{

	if (WidgetSwitcher->GetActiveWidget() == FloriologyMenu)
	{
		WidgetSwitcher->SetActiveWidget(MainCanvas);
	}
	else
	{
		WidgetSwitcher->SetActiveWidget(FloriologyMenu);

	}



}

void UInGameUI::AddNewMainAbility(UEBGameplayAbilityBase* Ability, AEmilia* Player)
{
	MainAbilities->AddMainAbility(Ability, Player);
}

void UInGameUI::SetHealthBar(float CurrentValue, float MaxValue)
{
	HealthBar->SetPercent(CurrentValue / MaxValue);
	ChangeHealthBarColor(CurrentValue/MaxValue);
}

void UInGameUI::NewAbilityFlowerGiven(UAbilityFlowerItem* Flower)
{
	AbilityFlowerList->AddItem(Flower);

}

void UInGameUI::ToggleMenu(bool ShouldToggle, float health, float maxHealth, float strength, float mag, float def, float res, float wepAug)
{
	if (ShouldToggle)
	{
		WidgetSwitcher->SetActiveWidget(MenuCanvas);
	}
	else
	{
		WidgetSwitcher->SetActiveWidget(MainCanvas);

	}
	StatsWidget->SetAllStatTexts(FString::FromInt(health),
		FString::FromInt(maxHealth), 
		FString::FromInt(strength), 
		FString::FromInt(mag), 
		FString::FromInt(def), 
		FString::FromInt(res),
		FString::FromInt(wepAug));
}

void UInGameUI::EnableCreationWidget(UAbilityFlowerItem* FlowerItem)
{
	TSubclassOf<UEBGameplayAbilityBase> abilityForRecipe = Gamemode->GetAbilityForCombination({ FlowerOne, FlowerItem });


	if (abilityForRecipe)
	{
		CraftingWidget->GetCreationWidget()->SetCreationBox(FlowerItem, abilityForRecipe);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("it doesn't exist"));

	}

}


void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
	AbilityFlowerList->OnEntryWidgetGenerated().AddUObject(this, &UInGameUI::HandleNewFlowerEntry);

	Gamemode = Cast<AEverbloomGameModeBase>(UGameplayStatics::GetGameMode(this));
	CraftingWidget->OnCreationWidget.AddDynamic(this, &UInGameUI::EnableCreationWidget);
}

void UInGameUI::HandleFlowerFromEntry(UAbilityFlowerItem* FlowerGiven)
{
	//flower one does not exist, assign the flower clicked as FlowerOne.
	if (!FlowerOne)
	{
		FlowerOne = FlowerGiven;
		CraftingWidget->SetFlowerOneImage(FlowerOne->GetItemIcon(), FlowerOne->GetItemName());
		return;
	}
	else
	{
		//flower one has been chosen. Assign flower two and then do something to let player know
		//if valid recipe based off of FlowerOne's recipe TMap.
		FlowerTwo = FlowerGiven;
		TSubclassOf<UEBGameplayAbilityBase> abilityForRecipe = Gamemode->GetAbilityForCombination({ FlowerOne, FlowerTwo });
		if (abilityForRecipe)
		{
			CraftingWidget->SetFlowerTwoImage(FlowerTwo->GetItemIcon());
			CraftingWidget->EnableValidCombinationButton(abilityForRecipe);
			UE_LOG(LogTemp, Warning, TEXT("the ability for the recipe is: %s"), *abilityForRecipe->GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("not a valid recipe"));

		}
	}
}

void UInGameUI::SpawnUpgradeNodes(UAbilityFlowerItem* FlowerGiven)
{
	FlowerOne = FlowerGiven;
	CraftingWidget->SetFlowerOneImage(FlowerGiven->GetItemIcon(), FlowerGiven->GetItemName());
	CraftingWidget->ClearNodes();

	TArray<FRecipe> Recipes = Gamemode->GetFlowerRecipes();

	for (FRecipe Recipe : Recipes)
	{
		if (Recipe.GetItems().Contains(FlowerOne->GetClass()))
		{
			UAbilityFlowerItem* Flower = Gamemode->GetRemainingFlowerFromRecipe(Recipe, FlowerOne->GetClass());
			CraftingWidget->AddToNodeEntryList(Flower);

		}
	}
	

}

void UInGameUI::HandleNewFlowerEntry(UUserWidget& UserWidget)
{
	UAbilityFlowerEntry* Entry = Cast<UAbilityFlowerEntry>(&UserWidget);
	if (Entry)
	{
		Entry->OnEntryClicked.AddDynamic(this, &UInGameUI::SpawnUpgradeNodes);
	}
}

