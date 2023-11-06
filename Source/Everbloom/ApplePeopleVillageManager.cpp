// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplePeopleVillageManager.h"
#include "AppleVillager.h"
#include "TaskVillageLocation.h"

// Sets default values
AApplePeopleVillageManager::AApplePeopleVillageManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AApplePeopleVillageManager::BeginPlay()
{
	Super::BeginPlay();
	SetManagerForVillagers();

}

// Called every frame
void AApplePeopleVillageManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AApplePeopleVillageManager::SetManagerForVillagers()
{
	for (AAppleVillager* Villager : Villagers)
	{
		Villager->AssignManger(this);
	}
}

void AApplePeopleVillageManager::FindTaskToDo(AAppleVillager* Villager)
{
	//in order to get in here all tasklocations must not be occupied
	ATaskVillageLocation* TaskLocation = nullptr;
	for (int i = 0; i < TaskLocations.Num(); i++)
	{
		//find a suitable location.
		if (!TaskLocations[i]->CheckOccupied())
		{
			TaskLocation = TaskLocations[i];
			break;
		}
	}
	if (TaskLocation)
	{
		Villager->SetWorkLocation(TaskLocation->GetActorLocation());
		TaskLocation->SetOccupied(Villager);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Critical Error: Task Location was never found"));
	}
}

