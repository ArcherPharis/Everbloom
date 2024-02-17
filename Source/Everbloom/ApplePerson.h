// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InteractableInterface.h"
#include "ApplePerson.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API AApplePerson : public ABaseCharacter, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AApplePerson();

	class UDialogueComponent* GetDialogueComponent() const { return DialogueComponent; }

	UFUNCTION(BlueprintImplementableEvent)
	void InteractEvent();

protected:
	virtual void InteractWith(AEmilia* Player);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UDialogueComponent* DialogueComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Apple")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "Apple")
	class UCameraComponent* Camera;
	
};
