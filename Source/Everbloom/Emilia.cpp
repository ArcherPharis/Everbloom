// Fill out your copyright notice in the Description page of Project Settings.


#include "Emilia.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "InteractableInterface.h"
#include "Camera/CameraComponent.h"
#include "EBAbilitySystemComponent.h"
#include "Components/TimelineComponent.h"
#include "InventoryComponent.h"

AEmilia::AEmilia()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	ToggleInventoryTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Inventory Timeline Comp"));

}

void AEmilia::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEmilia::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEmilia::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AEmilia::Interact);
		EnhancedInputComponent->BindAction(ToggleFlowerMenuAction, ETriggerEvent::Triggered, this, &AEmilia::ToggleFlowerMenu);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AEmilia::Jump);
		EnhancedInputComponent->BindAction(AbilityInputAction, ETriggerEvent::Triggered, this, &AEmilia::HandleAbilityInput);
		EnhancedInputComponent->BindAction(AttackEventInputAction, ETriggerEvent::Triggered, this, &AEmilia::BasicAttack);
		EnhancedInputComponent->BindAction(ToggleMenuAction, ETriggerEvent::Triggered, this, &AEmilia::ToggleMenu);
	}
}

void AEmilia::BeginPlay()
{
	Super::BeginPlay();
	DefaultSpringArmOffset = SpringArm->SocketOffset;
	DefaultSpringArmLength = SpringArm->TargetArmLength;

	FOnTimelineFloat InventoryTimeLineFloat;
	InventoryTimeLineFloat.BindUFunction(this, "UpdateSpringArmLocation");
	ToggleInventoryTimelineComponent->AddInterpFloat(InventoryAlpha, InventoryTimeLineFloat);

	InventoryComponent->InitializeInventory(GetMesh());
	GiveAbility(BasicAttackAbility, 3);
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void AEmilia::Move(const FInputActionValue& Value)
{
	const FVector2D CurrentValue = Value.Get<FVector2D>();

	AddMovementInput(FVector(Camera->GetForwardVector().X, Camera->GetForwardVector().Y, 0).GetSafeNormal(), CurrentValue.Y);
	AddMovementInput(Camera->GetRightVector(), CurrentValue.X);
}

void AEmilia::Look(const FInputActionValue& Value)
{
	const FVector2D CurrentValue = Value.Get<FVector2D>();
	AddControllerYawInput(CurrentValue.X);
	AddControllerPitchInput(CurrentValue.Y);
}

void AEmilia::Interact()
{
	FHitResult traceResult;
	FVector ViewLoc;
	FRotator ViewRot;
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(this);
	GetActorEyesViewPoint(ViewLoc, ViewRot);
	if (GetWorld()->LineTraceSingleByChannel(traceResult, ViewLoc, ViewLoc + ViewRot.Vector() * GrabRange, ECC_GameTraceChannel1, CollisionParameters))
	{
		if (traceResult.bBlockingHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found something interactable"));
			AActor* hitActor = traceResult.GetActor();
			IInteractableInterface* interactInferface = Cast<IInteractableInterface>(hitActor);
			interactInferface->InteractWith(this);

		}
	}
}

void AEmilia::ToggleFlowerMenu()
{
	
	OnToggleFlowerMenu.Broadcast();
}

void AEmilia::ToggleMenu()
{
	if (!bInInventory)
	{
		ToggleInventoryTimelineComponent->Play();
		bInInventory = true;
		OnToggleMenu.Broadcast(bInInventory);
	}
	else
	{
		ToggleInventoryTimelineComponent->Reverse();
		bInInventory = false;
		OnToggleMenu.Broadcast(bInInventory);
	}
}


void AEmilia::BasicAttack()
{
	FGameplayAbilitySpec* MeleeAbilitySpec = GetAbilitySystemComponent()->FindAbilitySpecFromClass(BasicAttackAbility);
	if (MeleeAbilitySpec->IsActive())
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, BasicAttackCombo, FGameplayEventData());
	}
	else
	{
		GetAbilitySystemComponent()->TryActivateAbilityByClass(BasicAttackAbility);
	}
}

void AEmilia::HandleAbilityInput(const FInputActionValue& InputActionValue)
{
	UE_LOG(LogTemp, Warning, TEXT("%f"), InputActionValue.Get<float>());
	GetAbilitySystemComponent()->AbilityLocalInputPressed(InputActionValue.Get<float>());
}

void AEmilia::UpdateSpringArmLocation(float Alpha)
{
	UE_LOG(LogTemp, Warning, TEXT("Updating spring arm alhpha: %f"), Alpha);
	SpringArm->TargetArmLength = FMath::Lerp(DefaultSpringArmLength, InventoryArmLength, Alpha);
	SpringArm->SocketOffset = FMath::Lerp(DefaultSpringArmOffset, InventorySocketLocation, Alpha);

	
}

