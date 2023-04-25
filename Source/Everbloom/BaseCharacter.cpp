// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "EBAbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/WidgetComponent.h"
#include "EBAttributeSet.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<UEBAbilitySystemComponent>("AbilitySystemComp");
	AttributeSet = CreateDefaultSubobject<UEBAttributeSet>("AttributeSet");
	HUDWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComp"));
	HUDWidget->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	ApplyInitialEffect();
	for (auto& Ability : InitialAbilities)
	{
		GiveAbility(Ability.Value, static_cast<int32>(Ability.Key));
	}


	if (AbilitySystemComp)
	{
		AbilitySystemComp->InitAbilityActorInfo(this, this);
		AbilitySystemComp->GenericConfirmInputID = static_cast<int32>(EAbilityInputID::Confirm);
		AbilitySystemComp->GenericCancelInputID = static_cast<int32>(EAbilityInputID::Cancel);

	}
	
}

void ABaseCharacter::ApplyEffectToSelf(const TSubclassOf<class UGameplayEffect>& effectToApply, int level)
{
	FGameplayEffectSpecHandle Spec = AbilitySystemComp->MakeOutgoingSpec(effectToApply, level, AbilitySystemComp->MakeEffectContext());
	AbilitySystemComp->ApplyGameplayEffectSpecToSelf(*Spec.Data);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::ApplyInitialEffect()
{
	if (InitialEffects.Num() > 0)
	{
		for (auto& effect : InitialEffects)
		{
			ApplyEffectToSelf(effect);
		}
	}
}

FGameplayAbilitySpec* ABaseCharacter::GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility, int inputID, bool broadCast, int level)
{
	FGameplayAbilitySpecHandle specHandle = AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(newAbility, -1, inputID));

	FGameplayAbilitySpec* spec = AbilitySystemComp->FindAbilitySpecFromHandle(specHandle);
	return spec;
}

