// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "EBAbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/WidgetComponent.h"
#include "EBAttributeSet.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

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
	PerceptionStimuliComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("PerceptionStimuliComp");
}

void ABaseCharacter::RotateTowardsLockedTarget()
{
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
	AttributeSet->OnManaAttributeChanged.AddDynamic(this, &ABaseCharacter::HandleCharacterMana);
}

void ABaseCharacter::HandleCharacterHealth(float NewValue, float OldValue)
{
	if (NewValue <= 0)
	{
		OnDead.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ouch"));
	}
	

}

void ABaseCharacter::HandleCharacterMana(float NewValue, float MaxHealth)
{
}




void ABaseCharacter::MoveToTarget(AActor* TargetActor)
{
	if (!TargetActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveToTarget: Invalid target actor!"));
		return;
	}

	FVector StartLocation = GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();

	const float DesiredDistance = 75.0f;
	const float MaxMovementSpeed = 60000.0f;

	FVector MovementDirection = (TargetLocation - StartLocation).GetSafeNormal();
	float DistanceToTarget = FVector::Distance(StartLocation, TargetLocation);

	// Rotate the character to face the target
	FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
	TargetRotation.Pitch = 0;
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds, 40.f));

	if (DistanceToTarget > DesiredDistance)
	{
		// Calculate the desired movement speed based on distance
		float MovementSpeed = FMath::Clamp(MaxMovementSpeed * (DistanceToTarget + DesiredDistance), 0, MaxMovementSpeed);

		// Calculate the movement amount for this frame
		float MaxMovementAmount = MovementSpeed * GetWorld()->DeltaTimeSeconds;
		float MovementAmount = FMath::Min(DistanceToTarget - DesiredDistance, MaxMovementAmount);

		// Calculate the new location for the character
		FVector NewLocation = StartLocation + MovementDirection * MovementAmount * 6;

		// Smoothly interpolate to the new location
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), NewLocation, GetWorld()->DeltaTimeSeconds, 5.0f));
	}


}

void ABaseCharacter::SetKiller(ABaseCharacter* KilledBy)
{
	Killer = KilledBy;
	UE_LOG(LogTemp, Warning, TEXT("My killer was: %s"), *Killer->GetName());
}

FGameplayAbilitySpec* ABaseCharacter::GiveAbility(const TSubclassOf<class UGameplayAbility>& newAbility, int inputID, bool broadCast, int level)
{
	FGameplayAbilitySpecHandle specHandle = AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(newAbility, -1, inputID));

	FGameplayAbilitySpec* spec = AbilitySystemComp->FindAbilitySpecFromHandle(specHandle);
	return spec;
}

