// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "Emilia.generated.h"

class AAbilityFlower;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnToggleFlowerMenu);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_EightParams(FOnToggleMenu, bool, Toggle, float, currentHP, float, maxHP, float, str, float, mag, float, def, float, res, float, WeaponDamage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSendTip, FText, Text);


/**
 * 
 */
UCLASS()
class EVERBLOOM_API AEmilia : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AEmilia();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	void StartAim();
	void EndAim();

	void GiveMainAbility(TSubclassOf<class UGameplayAbility> Ability, int input = -1);

	virtual void Tick(float DeltaTime) override;

	void LookAtTarget(AActor* Target);

	AActor* GetLockedOnTarget() const { return LockedOnTarget; }

	UFUNCTION(BlueprintImplementableEvent)
	void RotateToTargetEvent(const AActor* Target);
	virtual void RotateTowardsLockedTarget() override;

	UFUNCTION(BlueprintPure, Category = "Emilia")
	class UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	class UCameraComponent* GetCameraComponent() const { return Camera; }
	FOnToggleFlowerMenu OnToggleFlowerMenu;
	FOnToggleMenu OnToggleMenu;
	FOnSendTip OnSentTip;
	

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* MappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* InteractAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* ToggleFlowerMenuAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* AbilityInputAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* AttackEventInputAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ToggleMenuAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LockOnAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LockOnToggleAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* CastingAction;

	void InitMove();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LockOnToggle(const FInputActionValue& Value);
	void Interact();
	UFUNCTION(BlueprintCallable, Category = "Emilia")
	void Interact(AActor* ActorToInteractWith);
	void ToggleFlowerMenu();
	void ToggleMenu();
	void LockOn();
	void CharacterJump();
	void CastCurrentMagic();
	void CastCurrentMagicInputReleased();
	

private:

	void InitSpecialAbilities();
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	class USpringArmComponent* SpringArm;

	void BasicAttack();

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> BasicAttackAbility;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> AirAttackAbility;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> JumpAbility;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> DoubleJumpAbility;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> MovementAbility;


	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	FGameplayTag BasicAttackCombo;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	FGameplayTag FireProjectileTag;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	FGameplayTag EndAbilityTag;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	FGameplayTag MovementTagX;
	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	FGameplayTag MovementTagY;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float GrabRange = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	UInventoryComponent* InventoryComponent;




	void HandleAbilityInput(const FInputActionValue& InputActionValue);

	UPROPERTY()
	class UTimelineComponent* InventoryTimelineComponent;
	UPROPERTY()
	class UTimelineComponent* DisengageLockonTimelineComponent;
	UTimelineComponent* StartAimTimeline;

	UPROPERTY(EditDefaultsOnly, Category = "SpringArmAlphas")
	UCurveFloat* InventoryAlpha;

	UPROPERTY(EditDefaultsOnly, Category = "SpringArmAlphas")
	UCurveFloat* DisengageLockOnAlpha;

	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	UCurveFloat* AimAlpha;

	UFUNCTION()
	void UpdateSpringArmLocation(float Alpha);
	UFUNCTION()
	void UpdateSpringArmFromLockon(float Alpha);
	UFUNCTION()
	void UpdateAim(float Alpha);

	FVector  DefaultSpringArmOffset;
	float  DefaultSpringArmLength;

	UPROPERTY(EditDefaultsOnly, Category = "LockOn")
	FVector LockOnSpringArmOffset {0.0f, 0.0f, 90.0f};

	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	FVector AimSpringArmOffset {0.0f, 0.0f, 90.0f};

	UPROPERTY(EditDefaultsOnly, Category = "Aiming")
	float AimArmLength = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	float InventoryArmLength = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	FVector InventorySocketLocation{0.0f, 125.0f, 50.0f};

	UPROPERTY(VisibleAnywhere)
	bool bInInventory = false;

	bool bIsAiming = false;

	//todo, getting quite hefty, consider moving to a "LockOnComponent" or something.
	UPROPERTY(VisibleAnywhere)
	AActor* LockedOnTarget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ALockOnCapturer> LockOnCapturerClass;

	UPROPERTY(EditDefaultsOnly)
	float LockOnRange = 2500.f;
	
	AActor* GetClosestTarget(TArray<AActor*> Targets, float& Distance);

	UPROPERTY()
	class AEBPlayerController* PlayerCont;


	bool GetActorScreenPos(const AActor* Actor, FVector2D& outPOS) const;

	virtual void MoveToTarget(AActor* TargetActor) override;

	void Landed(const FHitResult& Hit) override;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Events")
	FGameplayTag OnLandEventTag;
};
