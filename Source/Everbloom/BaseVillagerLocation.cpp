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
	OnOccupied.Broadcast(this);
}

void ABaseVillagerLocation::SetVacant()
{
	OnVacant.Broadcast(this, CurrentVillager);
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

void ABaseVillagerLocation::StartOccupyTimer()
{
	float TimeVariable = FMath::RandRange(25.f, 65.f);
	GetWorld()->GetTimerManager().SetTimer(OccupyTimerHandle, this, &ABaseVillagerLocation::SetVacant, TimeVariable, false);
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

