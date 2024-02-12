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

	UFUNCTION(BlueprintCallable)
	void GiveAbilityToUI(class UEBGameplayAbilityBase* AbilityToGive, class AEmilia* PlayerToGive);

	UUserWidget* PCCreateWidget(TSubclassOf<UUserWidget> WidgetClass);

protected:


private:
	class AEmilia* Player;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UInGameUI> InGameUIClass;

	UPROPERTY()
	UInGameUI* InGameUI;

	UFUNCTION()
	void SwitchToFloriologyScreen();

	UFUNCTION()
	void PlayerChangedWeapon(class AWeapon* NewWeapon);

	UFUNCTION()
	void PlayerChangedMagic(class UEBGameplayAbilityBase* NewMagic);

	
};
