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
        float OldHealthValue = GetHealth() - Data.EvaluatedData.Magnitude;
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
        float NewHealthValue = GetHealth();

        OnHealthAttributeChanged.Broadcast(NewHealthValue, GetMaxHealth(), OldHealthValue);
    }

    if (Data.EvaluatedData.Attribute == GetManaAttribute())
    {
        SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
        float NewManaValue = GetMana();
        float OldManaValue = NewManaValue - Data.EvaluatedData.Magnitude;

        OnManaAttributeChanged.Broadcast(NewManaValue, GetMaxMana());
    }

    if (Data.EvaluatedData.Attribute == GetStrengthAttribute())
    {
        SetStrength(FMath::Clamp(GetStrength(), 0.f, 999.f));
    }

    if (Data.EvaluatedData.Attribute == GetDefenseAttribute())
    {
        SetDefense(FMath::Clamp(GetDefense(), 0.f, 999.f));
    }

    if (Data.EvaluatedData.Attribute == GetMagicAttribute())
    {
        SetMagic(FMath::Clamp(GetMagic(), 0.f, 999.f));
    }

    if (Data.EvaluatedData.Attribute == GetResistanceAttribute())
    {
        SetResistance(FMath::Clamp(GetResistance(), 0.f, 999.f));
    }

    if (Data.EvaluatedData.Attribute == GetDewFruitAttribute())
    {
        SetDewFruit(FMath::Clamp(GetDewFruit(), 0.f, 99.f));
        OnDewfruitChanged.Broadcast(GetDewFruit());
    }
}
