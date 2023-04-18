// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "EBGameplayAbilityBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityCommitted);

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UEBGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintPure, Category = "EBAbility")
	FORCEINLINE class ABaseCharacter* GetAvatarAsCharacter() const { return AvatarCharacterBase; }

	FOnAbilityCommitted onAbilityCommitted;

protected:
	virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override;

private:
	class ABaseCharacter* AvatarCharacterBase;
	
};
