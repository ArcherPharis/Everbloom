// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleVillager.h"
#include "ApplePeopleVillageManager.h"
#include "VillagerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


void AAppleVillager::AssignManger(AApplePeopleVillageManager* Mana)
{
	Manager = Mana;
}

void AAppleVillager::SetWorkLocation(FVector NewLocation, ATaskVillageLocation* Location)
{
	if (AIController)
	{
		AIController->GetBlackboardComponent()->ClearValue("VibeLocation");
		AIController->GetBlackboardComponent()->SetValueAsVector("TaskLocation", NewLocation);
	}
}

void AAppleVillager::SetVibeLocation(FVector NewLocation, AVillageVibeLocation* Location)
{
	if (AIController)
	{
		AIController->GetBlackboardComponent()->ClearValue("TaskLocation");
		AIController->GetBlackboardComponent()->SetValueAsVector("VibeLocation", NewLocation);
	}
}

void AAppleVillager::BeginPlay()
{
	Super::BeginPlay();
	AIController = Cast<AVillagerAIController>(GetOwner());
	if (AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got Our AIController!"));
	}

	if (Manager)
	{
		//temp, the manager will decide each apple person's task at start.
		//Manager->FindTaskToDo(this);
	}
}

void AAppleVillager::InteractWith(AEmilia* Player)
{
	Super::InteractWith(Player);
}
