// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseVillagerLocation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOccupied, ABaseVillagerLocation*, Location);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnVacant, ABaseVillagerLocation*, Location, class AAppleVillager*, Villager);


UCLASS()
class EVERBLOOM_API ABaseVillagerLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseVillagerLocation();

	FOnOccupied OnOccupied;
	FOnVacant OnVacant;
	void SetOccupied(class AAppleVillager* CurrentVillagerToSet);
	void SetVacant();
	bool CheckOccupied();
	void StartOccupyTimer();
	AAppleVillager* GetCurrentVillagerOccupyingSpace() const { return CurrentVillager; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Location")
	class AAppleVillager* CurrentVillager;

	UPROPERTY(EditAnywhere, Category = "Location")
	TArray<UAnimMontage*> MontagesToPlay;

	FTimerHandle OccupyTimerHandle;

};
