// Fill out your copyright notice in the Description page of Project Settings.


#include "EBPlayerController.h"
#include "Emilia.h"
#include "InventoryComponent.h"
#include "EnhancedInputSubsystems.h"
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
	}
}



void AEBPlayerController::SwitchToFloriologyScreen()
{
	InGameUI->SwitchToFloriology();
}
