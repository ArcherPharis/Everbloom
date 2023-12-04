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
#include "Weapon.h"

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
		Player->GetInventoryComponent()->OnChangedWeapon.AddDynamic(this, &AEBPlayerController::PlayerChangedWeapon);
		Player->GetInventoryComponent()->OnChangedMagic.AddDynamic(this, &AEBPlayerController::PlayerChangedMagic);
		Player->GetInventoryComponent()->OnLifedewChanged.AddDynamic(InGameUI, &UInGameUI::SetLifedewAmount);
		Player->GetAttributeSet()->OnHealthAttributeChanged.AddDynamic(InGameUI, &UInGameUI::SetHealthBar);
		Player->GetAttributeSet()->OnManaAttributeChanged.AddDynamic(InGameUI, &UInGameUI::SetManaBar);
		Player->GetAttributeSet()->OnDewfruitChanged.AddDynamic(InGameUI, &UInGameUI::SetDewfruitText);
		Player->OnSentTip.AddDynamic(InGameUI, &UInGameUI::CreateNewTip);
		Player->OnObtainAbilityFlower.AddDynamic(InGameUI, &UInGameUI::AddToFlowerNotificationBox);
		Player->GetInventoryComponent()->OnAddNewWeapon.AddDynamic(InGameUI, &UInGameUI::AddNewWeaponToStats);
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

void AEBPlayerController::PlayerChangedWeapon(AWeapon* NewWeapon)
{
	InGameUI->ChangeCurrentEquippedWeapon(NewWeapon->GetWeaponIcon(), NewWeapon->GetWeaponName());
}

void AEBPlayerController::PlayerChangedMagic(UEBGameplayAbilityBase* NewMagic)
{
	InGameUI->ChangeCurrentEquippedMagic(NewMagic->GetIcon(), NewMagic->GetAbilityName());
}

