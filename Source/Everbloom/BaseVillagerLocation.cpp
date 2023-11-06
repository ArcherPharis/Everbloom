// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVillagerLocation.h"

// Sets default values
ABaseVillagerLocation::ABaseVillagerLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseVillagerLocation::SetOccupied(AAppleVillager* CurrentVillagerToSet)
{
	CurrentVillager = CurrentVillagerToSet;
}

void ABaseVillagerLocation::SetVacant()
{
	CurrentVillager = nullptr;
}

bool ABaseVillagerLocation::CheckOccupied()
{
	if (CurrentVillager)
	{
		return true;
	}
	return false;
}

// Called when the game starts or when spawned
void ABaseVillagerLocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseVillagerLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

