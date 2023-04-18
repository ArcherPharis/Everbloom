// Fill out your copyright notice in the Description page of Project Settings.


#include "EBGameplayAbilityBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BaseCharacter.h"

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
