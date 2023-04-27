// Fill out your copyright notice in the Description page of Project Settings.


#include "Emilia.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/WidgetComponent.h"
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
	InventoryTimeLineFloat.BindUFunction(this, "UpdateSpringArmLocation");
	ToggleInventoryTimelineComponent->AddInterpFloat(InventoryAlpha, InventoryTimeLineFloat);

	InventoryComponent->InitializeInventory(GetMesh());
	//TODO when we swap weapons we need to make sure we also update the augment damage, can either be done here or inventory comp.
	if (InventoryComponent)
	{
		UEBAttributeSet* AS = GetAttributeSet();
		AS->SetWeaponAugmentDamage(InventoryComponent->GetCurrentWeaponDamage());
	}

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

void AEmilia::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
void AEmilia::LockOn()
{

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this;
	ALockOnCapturer* Capturer = GetWorld()->SpawnActor<ALockOnCapturer>(LockOnCapturerClass, GetActorTransform(), SpawnParams);
	TArray<AActor*> PotentialTargets = Capturer->GetAllTargetsInRange();
	if (PotentialTargets.Num() > 0)
	{
		float Distance = 0;
		if (LockedOnTarget)
		{
			UWidgetComponent* WidgetCpt = LockedOnTarget->FindComponentByClass<UWidgetComponent>();
			WidgetCpt->SetVisibility(false);
		}
		LockedOnTarget = GetClosestTarget(PotentialTargets, Distance);


		UWidgetComponent* WidgetCpt = LockedOnTarget->FindComponentByClass<UWidgetComponent>();
		if (WidgetCpt)
		{
			WidgetCpt->SetVisibility(true);
		}
	}
	else
	{
		return;
	}

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

		for (AActor* Enemy : EnemiesInRange)
		{
			if (Enemy == LockedOnTarget)
			{
				continue;
			}

			FVector ToEnemy = Enemy->GetActorLocation() - LockedOnTarget->GetActorLocation();
			float Distance = ToEnemy.Size();
			ToEnemy.Normalize();
			FVector CamForward = Camera->GetForwardVector();
			CamForward.Normalize();
			float DotProduct = FVector::DotProduct(CamForward, ToEnemy);
			//dotproduct gives incorrect product after first cycle
			if (DotProduct > 0.0f)
			{
				
				float DotProductRight = FVector::DotProduct(GetActorRightVector(), ToEnemy);


				if (Distance < BestDistance && DotProductRight > 0.0f)
				{
					BestDistance = Distance;
					BestEnemy = Enemy;
				}
			}



		}
		//current problem: BestEnemy seems to only get updated once
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
	UEBAttributeSet* AS = GetAttributeSet();
	if (!bInInventory)
	{
		ToggleInventoryTimelineComponent->Play();
		bInInventory = true;
		OnToggleMenu.Broadcast(bInInventory, AS->GetHealth(), AS->GetMaxHealth(), AS->GetStrength(), AS->GetMagic(), AS->GetDefense(), AS->GetResistance(), AS->GetWeaponAugmentDamage());
	}
	else
	{
		ToggleInventoryTimelineComponent->Reverse();
		bInInventory = false;
		OnToggleMenu.Broadcast(bInInventory, AS->GetHealth(), AS->GetMaxHealth(), AS->GetStrength(), AS->GetMagic(), AS->GetDefense(), AS->GetResistance(), AS->GetWeaponAugmentDamage());

	}
}




void AEmilia::BasicAttack()
{
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

