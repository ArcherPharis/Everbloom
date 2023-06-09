// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "EBAbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TimelineComponent.h"
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
	BaseTransform = CreateDefaultSubobject<USceneComponent>(TEXT("Base Transform"));
	BaseTransform->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitAttributeEvents();
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

void ABaseCharacter::EnableAiming(bool IsCurrentlyAiming)
{
	bIsAiming = IsCurrentlyAiming;
	if (bIsAiming)
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		bUseControllerRotationYaw = true;
	}
	else
	{
		GetCharacterMovement()->bOrientRotationToMovement = true;
		bUseControllerRotationYaw = false;
	}
}

void ABaseCharacter::InitAttributeEvents()
{
	AttributeSet->OnHealthAttributeChanged.AddDynamic(this, &ABaseCharacter::HandleCharacterHealth);
}

void ABaseCharacter::HandleCharacterHealth(float NewValue, float MaxHealth)
{
	if (NewValue == 0)
	{

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ouch"));
	}
	

}



void ABaseCharacter::MoveToTarget(AActor* TargetActor)
{
	FVector StartLocation = GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();



	float DistanceToTarget = FVector::Distance(StartLocation, TargetLocation);

	const float AcceptableDistance = 200.f;


	//original values were 800 and 50.f if you need to revert.
	float BaseMovementSpeed = 8000.0f;
	float MovementSpeed = BaseMovementSpeed * (DistanceToTarget / 150.0f);

	FVector MovementDirection = (TargetLocation - StartLocation).GetSafeNormal();
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
	TargetRotation.Pitch = 0;
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds, 2000.5f));

	if (DistanceToTarget <= AcceptableDistance)
	{
		return;
	}
	float MaxMovementAmount = MovementSpeed * GetWorld()->DeltaTimeSeconds;
	float MovementAmount = FMath::Min(DistanceToTarget - AcceptableDistance, MaxMovementAmount);

	FVector NewLocation = StartLocation + MovementDirection * MovementAmount;
	SetActorLocation(NewLocation);


}

FGameplayAbilitySpec* ABaseCharacter::GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility, int inputID, bool broadCast, int level)
{
	FGameplayAbilitySpecHandle specHandle = AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(newAbility, -1, inputID));

	FGameplayAbilitySpec* spec = AbilitySystemComp->FindAbilitySpecFromHandle(specHandle);
	return spec;
}

