// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ApplePerson.h"
#include "AppleVillager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractedWith);

/**
 * 
 */
UCLASS()
class EVERBLOOM_API AAppleVillager : public AApplePerson
{
	GENERATED_BODY()

public:
	void AssignManger(class AApplePeopleVillageManager* Mana);
	class AApplePeopleVillageManager* GetManager() const { return Manager; }

	void SetWorkLocation(FVector NewLocation, class ATaskVillageLocation* Location);
	void SetVibeLocation(FVector NewLocation, class AVillageVibeLocation* Location);
	void PauseAIBehavior();
	void ResumeAIBehavior();
	void ChangeCurrentState(TEnumAsByte<struct EVillagerState> NewState);
	FOnInteractedWith OnInteractedWith;

protected:
	virtual void BeginPlay() override;

private:
	class AApplePeopleVillageManager* Manager;
	class AVillagerAIController* AIController;

	class ABaseVillagerLocation* CurrentLocation;
	virtual void InteractWith(AEmilia* Player);

	UFUNCTION()
	void ResumeVillagerLogic();
};
