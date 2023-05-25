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

	}
}

void AEBPlayerController::GiveAbilityToUI(UEBGameplayAbilityBase* AbilityToGive, AEmilia* PlayerToGive)
{
	//temporary, in future when the flowers are interacted with they will just broadcast this data.
	InGameUI->AddNewMainAbility(AbilityToGive, PlayerToGive);
}



void AEBPlayerController::SwitchToFloriologyScreen()
{
	InGameUI->SwitchToFloriology();
}

