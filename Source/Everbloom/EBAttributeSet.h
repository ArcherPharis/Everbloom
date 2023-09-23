// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EBAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthAttributeChanged, float, NewValue, float, OldValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaAttributeChanged, float, NewValue, float, OldValue);


/**
 * 
 */
UCLASS()
class EVERBLOOM_API UEBAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	FOnHealthAttributeChanged OnHealthAttributeChanged;
	FOnManaAttributeChanged OnManaAttributeChanged;


	UPROPERTY()
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEBAttributeSet, Health);

	UPROPERTY()
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UEBAttributeSet, MaxHealth);

	UPROPERTY()
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UEBAttributeSet, Mana);

	UPROPERTY()
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UEBAttributeSet, MaxMana);

	UPROPERTY()
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UEBAttributeSet, Strength);

	UPROPERTY()
	FGameplayAttributeData Magic;
	ATTRIBUTE_ACCESSORS(UEBAttributeSet, Magic);

	UPROPERTY()
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UEBAttributeSet, Defense);

	UPROPERTY()
	FGameplayAttributeData Resistance;
	ATTRIBUTE_ACCESSORS(UEBAttributeSet, Resistance);

	UPROPERTY()
	FGameplayAttributeData WeaponAugmentDamage;
	ATTRIBUTE_ACCESSORS(UEBAttributeSet, WeaponAugmentDamage);

	UPROPERTY()
	FGameplayAttributeData DewFruit;
	ATTRIBUTE_ACCESSORS(UEBAttributeSet, DewFruit);


	
};
