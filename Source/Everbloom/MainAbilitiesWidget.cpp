// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAbilitiesWidget.h"
#include "MainAbilityEntry.h"
#include "EBGameplayAbilityBase.h"
#include "Components/HorizontalBox.h"

void UMainAbilitiesWidget::AddMainAbility(UEBGameplayAbilityBase* Ability, AEmilia* Player)
{
	if (Ability)
	{
		for (UWidget* Child : AbilityEntryBox->GetAllChildren())
		{
			UMainAbilityEntry* ChildEntry = Cast<UMainAbilityEntry>(Child);
			if (ChildEntry->GetAbility() == Ability)
			{
				return;
			}
		}

		UMainAbilityEntry* Entry = CreateWidget<UMainAbilityEntry>(GetOwningPlayer(), MainAbilityEntryWidget);
		Entry->InitAbilityIcon(Ability->GetIcon(), Ability, Player);
		AbilityEntryBox->AddChild(Entry);
	}
}
