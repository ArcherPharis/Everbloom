// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ApplePerson.h"
#include "VillagerAIController.h"
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
	AAppleVillager();
	void SetWorkLocation(FVector NewLocation, class ATaskVillageLocation* Location);
	void SetVibeLocation(FVector NewLocation, class AVillageVibeLocation* Location);
	void ClearLocations();
	void ClearEmilia();
	void PauseAIBehavior();
	void ResumeAIBehavior();
	void StartFollowTimer();
	void ChangeCurrentState(TEnumAsByte<EVillagerState> NewState);
	void SpawnItemOnHead();
	TEnumAsByte<EVillagerState> GetCurrentState();
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

	void AskForTask();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> HeadSpawnedItemClass;
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SpawnLocation;

};
