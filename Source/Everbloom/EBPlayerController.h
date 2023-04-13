// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EBPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API AEBPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* newPawn) override;



private:

	class AEmilia* Player;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UInGameUI> InGameUIClass;

	UPROPERTY()
	UInGameUI* InGameUI;

	UFUNCTION()
	void SwitchToFloriologyScreen();
	
};
