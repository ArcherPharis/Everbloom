// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "Emilia.generated.h"

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

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* MappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LookAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Player")
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
		class UCameraComponent* Camera;
	
};
