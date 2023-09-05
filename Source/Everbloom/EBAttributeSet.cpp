// Fill out your copyright notice in the Description page of Project Settings.


#include "EBAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

void UEBAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
        float NewHealthValue = GetHealth();
        float OldHealthValue = NewHealthValue - Data.EvaluatedData.Magnitude;

        OnHealthAttributeChanged.Broadcast(NewHealthValue, GetMaxHealth());
    }

    if (Data.EvaluatedData.Attribute == GetManaAttribute())
    {
        SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
        float NewManaValue = GetMana();
        float OldManaValue = NewManaValue - Data.EvaluatedData.Magnitude;

        OnManaAttributeChanged.Broadcast(NewManaValue, GetMaxMana());
    }
}
