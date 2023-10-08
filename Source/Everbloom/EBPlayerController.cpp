// Fill out your copyright notice in the Description page of Project Settings.


#include "EBPlayerController.h"
#include "Emilia.h"
#include "InventoryComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EBAbilitySystemComponent.h"
#include "EBGameplayAbilityBase.h"
#include "GameplayEffectTypes.h"
#include "EBAttributeSet.h"
#include "InGameUI.h"

void AEBPlayerController::OnPossess(APawn* newPawn)
{
	Super::OnPossess(newPawn);
	Player = Cast<AEmilia>(newPawn);
	if (Player)
	{
		InGameUI = CreateWidget<UInGameUI>(this, InGameUIClass);
		InGameUI->AddToViewport();
		Player->OnToggleFlowerMenu.AddDynamic(this, &AEBPlayerController::SwitchToFloriologyScreen);
		Player->OnToggleMenu.AddDynamic(InGameUI, &UInGameUI::ToggleMenu);
		Player->GetInventoryComponent()->OnNewAbilityFlowerObtained.AddDynamic(InGameUI, &UInGameUI::NewAbilityFlowerGiven);
		Player->GetAttributeSet()->OnHealthAttributeChanged.AddDynamic(InGameUI, &UInGameUI::SetHealthBar);
		Player->GetAttributeSet()->OnManaAttributeChanged.AddDynamic(InGameUI, &UInGameUI::SetManaBar);
		Player->OnSentTip.AddDynamic(InGameUI, &UInGameUI::CreateNewTip);

	}
}

void AEBPlayerController::GiveAbilityToUI(UEBGameplayAbilityBase* AbilityToGive, AEmilia* PlayerToGive)
{
	InGameUI->AddNewMainAbility(AbilityToGive, PlayerToGive);
}



void AEBPlayerController::SwitchToFloriologyScreen()
{
	InGameUI->SwitchToFloriology();
}

