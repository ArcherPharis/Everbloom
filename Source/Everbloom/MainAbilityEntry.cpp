// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAbilityEntry.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "EBAbilitySystemComponent.h"
#include "Emilia.h"
#include "EBGameplayAbilityBase.h"

void UMainAbilityEntry::InitAbilityIcon(UTexture2D* IconToSet, UEBGameplayAbilityBase* AbilityForEntry, AEmilia* Emilia)
{
	AbilityIcon->SetBrushFromTexture(IconToSet);
	Ability = AbilityForEntry;
	if (Ability)
	{
		AbilitySystemComponent = Emilia->GetAbilitySystemComponent();
		
		AbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(Ability->GetClass());
		AbilitySpecHandle = AbilitySpec->Handle;
		Ability->onAbilityCommitted.AddDynamic(this, &UMainAbilityEntry::StartCooldownBar);
	}


}

void UMainAbilityEntry::SetAbilityCooldownBar(float CurrentDuration, float Duration)
{
	float CurrentProgress = Duration - CurrentDuration;
	CooldownBar->SetPercent(CurrentProgress / Duration);
}

void UMainAbilityEntry::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (bIsCoolingDown)
	{
		if (CooldownBar->GetPercent() == 1)
		{
			bIsCoolingDown = false;
			return;
		}
		StartCooldownBar();
	}
}

void UMainAbilityEntry::StartCooldownBar()
{
	bIsCoolingDown = true;
	float CurrentDuration;
	float MaxDuration;
	Ability->GetCooldownTimeRemainingAndDuration(AbilitySpecHandle, AbilitySystemComponent->AbilityActorInfo.Get(), CurrentDuration, MaxDuration);
	SetAbilityCooldownBar(CurrentDuration, MaxDuration);
}
