// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplePeopleVillageManager.h"
#include "AppleVillager.h"
#include "TaskVillageLocation.h"
#include "VillageVibeLocation.h"

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
	GetWorld()->GetTimerManager().SetTimer(DelegateDelay, this, &AApplePeopleVillageManager::BeginDelegate, 0.1f, false);

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

void AApplePeopleVillageManager::DelegateTasks()
{
	//we also need to check if there is an empty slots left, if not, go with the other option.


	for (AAppleVillager* Villager : Villagers)
	{
		int Decider = FMath::RandRange(0, 1);

		if (Decider == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("I will Do a Work Task!"));
			FindTaskToDo(Villager);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("I will Do a Vibe Task!"));
			GetVibing(Villager);

		}
	}
}

void AApplePeopleVillageManager::BeginDelegate()
{
	DelegateTasks();
}

void AApplePeopleVillageManager::BindLocations()
{
	for (ATaskVillageLocation* Location : TaskLocations)
	{
		//this should allow the manager to know WHICH location just got occupied so it can release
		//this location in x amount of time and grab its occupant if needed.
		Location->OnOccupied.AddDynamic(this, &AApplePeopleVillageManager::StartOccupyTimer);
	}
}

void AApplePeopleVillageManager::StartOccupyTimer(ABaseVillagerLocation* OccupiedLocation)
{
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
		UE_LOG(LogTemp, Warning, TEXT("%s"), *TaskLocation->GetName());
		Villager->SetWorkLocation(TaskLocation->GetActorLocation(), TaskLocation);
		TaskLocation->SetOccupied(Villager);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Critical Error: Task Location was never found"));
	}
}

void AApplePeopleVillageManager::GetVibing(AAppleVillager* Villager)
{
	AVillageVibeLocation* VibeLocation = nullptr;
	for (int i = 0; i < VibeLocations.Num(); i++)
	{
		//find a suitable location.
		if (!VibeLocations[i]->CheckOccupied())
		{
			VibeLocation = VibeLocations[i];
			break;
		}
	}
	if (VibeLocation)
	{
		Villager->SetVibeLocation(VibeLocation->GetActorLocation(), VibeLocation);
		VibeLocation->SetOccupied(Villager);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Critical Error: Vibe Location was never found"));
	}
}

