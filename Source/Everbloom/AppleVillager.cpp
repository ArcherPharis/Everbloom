// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleVillager.h"
#include "ApplePeopleVillageManager.h"
#include "VillagerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "DialogueComponent.h"
#include "DialogueWidget.h"


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

void AAppleVillager::PauseAIBehavior()
{
	if (AIController)
	{
		AIController->GetBrainComponent()->PauseLogic("Cuz we need to pause");
		AIController->StopMovement();
	}
}

void AAppleVillager::ResumeAIBehavior()
{
	if (AIController)
	{
		AIController->GetBrainComponent()->ResumeLogic("Cuz we need to resume");
		FAIRequestID RequestID;
		AIController->ResumeMove(RequestID);
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
	GetDialogueComponent()->OnDialogueExit.AddDynamic(this, &AAppleVillager::ResumeVillagerLogic);
}

void AAppleVillager::InteractWith(AEmilia* Player)
{
	Super::InteractWith(Player);
	OnInteractedWith.Broadcast();
}

void AAppleVillager::ResumeVillagerLogic()
{
	if (Manager)
	{
		Manager->ResumeAllApples();
	}
}

