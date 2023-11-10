// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ApplePeopleVillageManager.generated.h"

UCLASS()
class EVERBLOOM_API AApplePeopleVillageManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AApplePeopleVillageManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void FindTaskToDo(class AAppleVillager* Villager);
	void GetVibing(class AAppleVillager* Villager);
	void ResumeAllApples();
	bool CheckIfCanFollowEmilia();

private:
	void SetManagerForVillagers();
	void DelegateTasks();
	void BeginDelegate();
	void BindLocations();
	void AssignNewTask(AAppleVillager* Villager);
	UFUNCTION()
	void StartOccupyTimer(class ABaseVillagerLocation* OccupiedLocation);

	UFUNCTION()
	void LocationRelease(ABaseVillagerLocation* OccupiedLocation, AAppleVillager* Villager);

	UFUNCTION()
	void PauseAllApples();

	UPROPERTY(EditInstanceOnly, Category = "Villagers")
	TArray<class AAppleVillager*> Villagers;

	UPROPERTY(EditInstanceOnly, Category = "Villagers")
	TArray<class AVillageVibeLocation*> VibeLocations;

	UPROPERTY(EditInstanceOnly, Category = "Villagers")
	TArray<class ATaskVillageLocation*> TaskLocations;

	UPROPERTY(EditInstanceOnly, Category = "Villagers")
	TArray<class AAppleVillager*> CurrentFollowers;

	FTimerHandle DelegateDelay;

};
