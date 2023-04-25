// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "Emilia.generated.h"

class AAbilityFlower;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnToggleFlowerMenu);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_EightParams(FOnToggleMenu, bool, Toggle, float, currentHP, float, maxHP, float, str, float, mag, float, def, float, res, float, WeaponDamage);



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

	virtual void Tick(float DeltaTime) override;

	class UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }


	FOnToggleFlowerMenu OnToggleFlowerMenu;
	FOnToggleMenu OnToggleMenu;
	

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

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	void ToggleFlowerMenu();
	void ToggleMenu();
	void LockOn();
	

private:
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	class USpringArmComponent* SpringArm;

	void BasicAttack();

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	TSubclassOf<class UGameplayAbility> BasicAttackAbility;

	UPROPERTY(EditDefaultsOnly, Category = "GameplayAbility")
	FGameplayTag BasicAttackCombo;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float GrabRange = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	UInventoryComponent* InventoryComponent;




	void HandleAbilityInput(const FInputActionValue& InputActionValue);

	UPROPERTY()
	class UTimelineComponent* ToggleInventoryTimelineComponent;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* InventoryAlpha;

	UFUNCTION()
	void UpdateSpringArmLocation(float Alpha);

	FVector  DefaultSpringArmOffset;
	float  DefaultSpringArmLength;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	float InventoryArmLength = 200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	FVector InventorySocketLocation{0.0f, 125.0f, 50.0f};

	UPROPERTY(VisibleAnywhere)
	bool bInInventory = false;

	AActor* LockedOnTarget;

	UPROPERTY(EditDefaultsOnly)
	float LockOnRange = 2500.f;

	UPROPERTY()
	class AEBPlayerController* PlayerCont;
	
};
