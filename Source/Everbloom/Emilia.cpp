// Fill out your copyright notice in the Description page of Project Settings.


#include "Emilia.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework./CharacterMovementComponent.h"
#include "EBGameplayAbilityBase.h"
#include "LockOnCapturer.h"
#include "Kismet/KismetMathLibrary.h"
#include "EBAttributeSet.h"
#include "Components/InputComponent.h"
#include "EBPlayerController.h"
#include "InteractableInterface.h"
#include "Camera/CameraComponent.h"
#include "EBAbilitySystemComponent.h"
#include "Components/TimelineComponent.h"
#include "InventoryComponent.h"
#include "GA_Movement.h"

AEmilia::AEmilia()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	InventoryTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Inventory Timeline Comp"));
	DisengageLockonTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Disengage Timeline Comp"));


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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AEmilia::CharacterJump);
		EnhancedInputComponent->BindAction(AbilityInputAction, ETriggerEvent::Triggered, this, &AEmilia::HandleAbilityInput);
		EnhancedInputComponent->BindAction(AttackEventInputAction, ETriggerEvent::Triggered, this, &AEmilia::BasicAttack);
		EnhancedInputComponent->BindAction(ToggleMenuAction, ETriggerEvent::Triggered, this, &AEmilia::ToggleMenu);
		EnhancedInputComponent->BindAction(LockOnAction, ETriggerEvent::Triggered, this, &AEmilia::LockOn);
		EnhancedInputComponent->BindAction(LockOnToggleAction, ETriggerEvent::Triggered, this, &AEmilia::LockOnToggle);
	}
}

void AEmilia::BeginPlay()
{
	Super::BeginPlay();
	DefaultSpringArmOffset = SpringArm->SocketOffset;
	DefaultSpringArmLength = SpringArm->TargetArmLength;
	PlayerCont = Cast<AEBPlayerController>(GetOwner());
	FOnTimelineFloat InventoryTimeLineFloat;
	FOnTimelineFloat DisengageLockOnFloat;
	InventoryTimeLineFloat.BindUFunction(this, "UpdateSpringArmLocation");
	DisengageLockOnFloat.BindUFunction(this, "UpdateSpringArmFromLockon");

	InventoryTimelineComponent->AddInterpFloat(InventoryAlpha, InventoryTimeLineFloat);
	DisengageLockonTimelineComponent->AddInterpFloat(DisengageLockOnAlpha, DisengageLockOnFloat);

	InventoryComponent->InitializeInventory(GetMesh());
	//TODO when we swap weapons we need to make sure we also update the augment damage, can either be done here or inventory comp.
	if (InventoryComponent)
	{
		UEBAttributeSet* AS = GetAttributeSet();
		AS->SetWeaponAugmentDamage(InventoryComponent->GetCurrentWeaponDamage());
	}

	InitSpecialAbilities();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
	
}

void AEmilia::GiveMainAbility(TSubclassOf<class UGameplayAbility> Ability, int input)
{
	FGameplayAbilitySpec* Spec = GiveAbility(Ability, input);
	if (PlayerCont && Spec->Ability)
	{
		PlayerCont->GiveAbilityToUI(Cast<UEBGameplayAbilityBase>(Spec->Ability), this);
	}
}

void AEmilia::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LockedOnTarget)
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LockedOnTarget->GetActorLocation());
		FRotator InterpRot = FMath::RInterpTo(PlayerCont->GetControlRotation(), LookAtRotation, DeltaTime, 5.f);
		PlayerCont->SetControlRotation(InterpRot);
	}

}

void AEmilia::LookAtTarget(AActor* Target)
{
	if (Target)
	{
		FRotator Rotat = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LockedOnTarget->GetActorLocation());
		Rotat.Pitch = 0;
		SetActorRotation(Rotat);
	}
}

void AEmilia::InitMove()
{
	FGameplayAbilitySpec* MovementSpec = GiveAbility(MovementAbility);
}

void AEmilia::Move(const FInputActionValue& Value)
{
	GetAbilitySystemComponent()->TryActivateAbilityByClass(MovementAbility);
	const FVector2D CurrentValue = Value.Get<FVector2D>();
	FGameplayEventData EventDataX;
	EventDataX.EventMagnitude = CurrentValue.X;
	FGameplayEventData EventDataY;
	EventDataY.EventMagnitude = CurrentValue.Y;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, MovementTagX, EventDataX);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, MovementTagY, EventDataY);

}

void AEmilia::Look(const FInputActionValue& Value)
{
	const FVector2D CurrentValue = Value.Get<FVector2D>();

	if (LockedOnTarget)
	{
		AddControllerYawInput(0);
		AddControllerPitchInput(0);
	}
	else
	{
		AddControllerYawInput(CurrentValue.X);
		AddControllerPitchInput(CurrentValue.Y);
	}
	
	
}
void AEmilia::LockOn()
{

	if (LockedOnTarget)
	{
		UWidgetComponent* WidgetCpt = LockedOnTarget->FindComponentByClass<UWidgetComponent>();
		WidgetCpt->SetVisibility(false);
		LockedOnTarget = nullptr;
		DisengageLockonTimelineComponent->Play();
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this;
	ALockOnCapturer* Capturer = GetWorld()->SpawnActor<ALockOnCapturer>(LockOnCapturerClass, GetActorTransform(), SpawnParams);
	TArray<AActor*> PotentialTargets = Capturer->GetAllTargetsInRange();
	if (PotentialTargets.Num() > 0)
	{
		float Distance = 0;

		LockedOnTarget = GetClosestTarget(PotentialTargets, Distance);
		DisengageLockonTimelineComponent->Reverse();
		SpringArm->SocketOffset = LockOnSpringArmOffset;

		UWidgetComponent* WidgetCpt = LockedOnTarget->FindComponentByClass<UWidgetComponent>();
		if (WidgetCpt)
		{
			WidgetCpt->SetVisibility(true);
		}
	}
	else
	{
		SpringArm->SocketOffset = DefaultSpringArmOffset;
		return;
	}

}

void AEmilia::CharacterJump()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		GetAbilitySystemComponent()->TryActivateAbilityByClass(JumpAbility);
	}
	else
	{
		GetAbilitySystemComponent()->TryActivateAbilityByClass(DoubleJumpAbility);

	}
	

}

void AEmilia::InitSpecialAbilities()
{
	GiveAbility(BasicAttackAbility);
	GiveAbility(AirAttackAbility);
	GiveAbility(JumpAbility);
	//Double jump temp. Flower gives this.
	GiveAbility(DoubleJumpAbility);
	InitMove();
}

void AEmilia::LockOnToggle(const FInputActionValue& Value)
{
	float ToggledAxis = Value.Get<float>();

	if (LockedOnTarget)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = this;
		ALockOnCapturer* Capturer = GetWorld()->SpawnActor<ALockOnCapturer>(LockOnCapturerClass, GetActorTransform(), SpawnParams);
		TArray<AActor*> PotentialTargets = Capturer->GetAllTargetsInRange();
		TArray<AActor*> EnemiesInRange;
		AActor* BestEnemy = nullptr;
		float BestDistance = FLT_MAX;
		for (AActor* Actor : PotentialTargets)
		{
			EnemiesInRange.Add(Actor);
		}

		FVector2D CurrentTargetScreenLoc;
		GetActorScreenPos(LockedOnTarget, CurrentTargetScreenLoc);

		for (AActor* Enemy : EnemiesInRange)
		{
			if (Enemy == LockedOnTarget)
			{
				continue;
			}

			//FVector ToEnemy = Enemy->GetActorLocation() - LockedOnTarget->GetActorLocation();
			//FVector Right = Camera->GetRightVector();
			//float dot = FVector::DotProduct(ToEnemy.GetSafeNormal(), Right);
			//bool bothPos = dot > 0 && ToggledAxis > 0;
			//bool bothNeg = dot < 0 && ToggledAxis < 0;
			//if (dot * ToggledAxis > 0)
			//{

			//	FVector CurrentTargetToEnemy = Enemy->GetActorLocation() - LockedOnTarget->GetActorLocation();
			//	float CamViewDistance = FMath::Abs(FVector::DotProduct(CurrentTargetToEnemy, Right));

			//	if (CamViewDistance < BestDistance)
			//	{
			//		
			//		BestEnemy = Enemy;
			//		BestDistance = CamViewDistance;
			//	}

			FVector2D ScreenPos;
			if(!GetActorScreenPos(Enemy, ScreenPos))
			{

				continue;

			}
			float XOffset = ScreenPos.X - CurrentTargetScreenLoc.X;
			if (XOffset * ToggledAxis > 0)
			{
				float distance = FMath::Abs(XOffset);
				if (distance < BestDistance)
				{
					BestDistance = distance;
					BestEnemy = Enemy;
				}
			}


		}
		if (BestEnemy != nullptr)
		{
			
			if (LockedOnTarget)
			{
				UWidgetComponent* WidgetCpt = LockedOnTarget->FindComponentByClass<UWidgetComponent>();
				WidgetCpt->SetVisibility(false);
			}
			LockedOnTarget = BestEnemy;
			UWidgetComponent* WidgetCpt = LockedOnTarget->FindComponentByClass<UWidgetComponent>();
			if (WidgetCpt)
			{
				WidgetCpt->SetVisibility(true);
			}
		}
	}
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
	UEBAttributeSet* AS = GetAttributeSet();
	if (!bInInventory)
	{
		InventoryTimelineComponent->Play();
		bInInventory = true;
		OnToggleMenu.Broadcast(bInInventory, AS->GetHealth(), AS->GetMaxHealth(), AS->GetStrength(), AS->GetMagic(), AS->GetDefense(), AS->GetResistance(), AS->GetWeaponAugmentDamage());
	}
	else
	{
		InventoryTimelineComponent->Reverse();
		bInInventory = false;
		OnToggleMenu.Broadcast(bInInventory, AS->GetHealth(), AS->GetMaxHealth(), AS->GetStrength(), AS->GetMagic(), AS->GetDefense(), AS->GetResistance(), AS->GetWeaponAugmentDamage());

	}
}




void AEmilia::BasicAttack()
{
	if (GetCharacterMovement()->IsFalling())
	{
		GetAbilitySystemComponent()->TryActivateAbilityByClass(AirAttackAbility);
		return;
	}

	FGameplayAbilitySpec* MeleeAbilitySpec = GetAbilitySystemComponent()->FindAbilitySpecFromClass(BasicAttackAbility);
	if (MeleeAbilitySpec->IsActive())
	{
		if (LockedOnTarget)
		{
			FRotator Rotat = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LockedOnTarget->GetActorLocation());
			Rotat.Pitch = 0;
			SetActorRotation(Rotat);
		}
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

void AEmilia::UpdateSpringArmFromLockon(float Alpha)
{
	SpringArm->SocketOffset = FMath::Lerp(LockOnSpringArmOffset, DefaultSpringArmOffset, Alpha);
}

AActor* AEmilia::GetClosestTarget(TArray<AActor*> Targets, float& Distance)
{
	AActor* ClosestTarget = nullptr;
	//because our radius of capturer if 1500
	float ClosestDistance = 1600;

	for (AActor* Target : Targets)
	{
		float DistTo = Target->GetDistanceTo(this);
		if (DistTo < ClosestDistance)
		{
			ClosestDistance = DistTo;
			ClosestTarget = Target;
		}
	}
	Distance = ClosestDistance;
	return ClosestTarget;
}

bool AEmilia::GetActorScreenPos(const AActor* Actor, FVector2D& outPOS) const
{
	if (PlayerCont)
	{
		return PlayerCont->ProjectWorldLocationToScreen(Actor->GetActorLocation(), outPOS, true);
	}
	return false;
}

void AEmilia::MoveToTarget(AActor* TargetActor)
{
	if (LockedOnTarget)
	{
		Super::MoveToTarget(LockedOnTarget);
	}
	else
	{
		Super::MoveToTarget(TargetActor);
	}
}

void AEmilia::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, OnLandEventTag, FGameplayEventData());
}


