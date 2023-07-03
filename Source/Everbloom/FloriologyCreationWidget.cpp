// Fill out your copyright notice in the Description page of Project Settings.


#include "FloriologyCreationWidget.h"
#include "AbilityFlowerItem.h"
#include "EBGameplayAbilityBase.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UFloriologyCreationWidget::SetCreationBox(UAbilityFlowerItem* FlowerItem, TSubclassOf<UEBGameplayAbilityBase> Ability)
{
	SetVisibility(ESlateVisibility::Visible);
	RequiredItemText->SetText(FlowerItem->GetItemName());
	SpellNameText->SetText(Ability.GetDefaultObject()->GetAbilityName());
	DescriptionText->SetText(Ability.GetDefaultObject()->GetAbilityDescription());
	SpellIcon->SetBrushFromTexture(Ability.GetDefaultObject()->GetIcon());
}
