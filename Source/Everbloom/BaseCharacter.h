// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "EBGameplayAbilityTypes.h"
#include "GameplayAbilitySpec.h"
#include "BaseCharacter.generated.h"

UCLASS()
class EVERBLOOM_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	class UWidgetComponent* GetCharacterWidgetComponent() const { return HUDWidget; }

	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "GameplayAbility")
	void ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply, int level = -1);

	FGameplayAbilitySpec* GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility, int inputID = -1, bool broadCast = true, int level = 0);

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class UEBAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComp; }
	FORCEINLINE class UEBAttributeSet* GetAttributeSet() const { return AttributeSet; }

	void ApplyInitialEffect();

private:
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



	

};
