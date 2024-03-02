// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "EBGameplayAbilityTypes.h"
#include "GameplayAbilitySpec.h"
#include "GenericTeamAgentInterface.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

UCLASS()
class EVERBLOOM_API ABaseCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	class UWidgetComponent* GetCharacterWidgetComponent() const { return HUDWidget; }

	virtual void RotateTowardsLockedTarget();

	bool IsDead() const;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeathEvent();

	FOnDead OnDead;
	UFUNCTION(BlueprintCallable, Category = "GameplayAbility")
	void ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply, int level = -1);

	UFUNCTION(BlueprintPure, Category = "Base Character")
	UAnimMontage* GetFlinchMontage() const { return FlinchMontage; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	UFUNCTION()
	virtual void HandleCharacterMana(float NewValue, float OldValue);

	UFUNCTION()
	virtual void HandleCharacterHealth(float NewValue, float MaxHealth);
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FGameplayAbilitySpec* GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility, int inputID = -1, bool broadCast = true, int level = 0);


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	class UEBAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComp; }
	FORCEINLINE class UEBAttributeSet* GetAttributeSet() const { return AttributeSet; }

	void ApplyInitialEffect();

	void EnableAiming(bool IsCurrentlyAiming);

	void InitAttributeEvents();

	USceneComponent* GetBaseLocation() const { return BaseTransform; }

	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void MoveToTarget(AActor* TargetActor);

	/** Assigns Team Agent to given TeamID */
	FORCEINLINE virtual void SetGenericTeamId(const FGenericTeamId& ID) { TeamID = ID; }

	/** Retrieve team identifier in form of FGenericTeamId */
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const { return TeamID; }

	void SetKiller(ABaseCharacter* KilledBy);
	ABaseCharacter* GetKiller() const { return Killer; }

private:

	UPROPERTY(EditAnywhere, Category = "AI")
	FGenericTeamId TeamID;

	UPROPERTY()
	class UAIPerceptionStimuliSourceComponent* PerceptionStimuliComp;


	UPROPERTY()
	UEBAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY()
	UEBAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TMap<EAbilityInputID, TSubclassOf<class UGameplayAbility>> InitialAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TArray <TSubclassOf<class UGameplayEffect>> InitialEffects;

	//TODO: Move this onto Enemy class as the player does not need this.
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	class UWidgetComponent* HUDWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	USceneComponent* BaseTransform;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* DeathMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* FlinchMontage;

	bool bIsAiming = false;

	UPROPERTY(EditDefaultsOnly)
	UCurveVector* VectorCurve;

	UPROPERTY()
	ABaseCharacter* Killer;

	UPROPERTY(EditDefaultsOnly, Category = "Status Tags")
	FGameplayTag StunTag;
	UPROPERTY(EditDefaultsOnly, Category = "Status Tags")
	bool bCanBeStunned = false;

	void StunTagChanged(const FGameplayTag tag, int32 count);

	void Disable();
	void RecoverFromDisable();

	void PauseAILogic(const FString& Reason = "Status");
	void ResumeAILogic(const FString& Reason = "Status");






	



	

};
