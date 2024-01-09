// Fill out your copyright notice in the Description page of Project Settings.


#include "EBGameplayAbilityBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BaseCharacter.h"
#include "EBAbilitySystemComponent.h"

void UEBGameplayAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	AvatarCharacterBase = Cast<ABaseCharacter>(GetAvatarActorFromActorInfo());
}

bool UEBGameplayAbilityBase::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
{
	if (Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags))
	{
		UEBGameplayAbilityBase* CDO = Cast<UEBGameplayAbilityBase>(GetClass()->GetDefaultObject());
		if (CDO)
		{
			CDO->onAbilityCommitted.Broadcast();
		}
		return true;
	}
	return false;
}

void UEBGameplayAbilityBase::ApplyStunEffectToTarget(const AActor* Target)
{
	UEBAbilitySystemComponent* ASC = Target->FindComponentByClass<UEBAbilitySystemComponent>();
	if (ASC)
	{
		FGameplayEffectSpecHandle Handle = ASC->MakeOutgoingSpec(StunEffect, -1, ASC->MakeEffectContext());
		ASC->ApplyGameplayEffectSpecToSelf(*Handle.Data.Get());
	}
}

void UEBGameplayAbilityBase::ApplyStunEffectToTarget(FGameplayAbilityTargetDataHandle TargetData)
{
	K2_ApplyGameplayEffectSpecToTarget(MakeOutgoingGameplayEffectSpec(StunEffect), TargetData);
}
