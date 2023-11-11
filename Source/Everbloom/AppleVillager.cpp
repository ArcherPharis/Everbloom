// Fill out your copyright notice in the Description page of Project Settings.


#include "AppleVillager.h"
#include "ApplePeopleVillageManager.h"
#include "VillagerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "DialogueComponent.h"
#include "DialogueWidget.h"
#include "Emilia.h"


void AAppleVillager::AssignManger(AApplePeopleVillageManager* Mana)
{
	Manager = Mana;
}

AAppleVillager::AAppleVillager()
{
	SpawnLocation = CreateDefaultSubobject<USceneComponent>("Item Spawn Location");
	SpawnLocation->SetupAttachment(RootComponent);
}

void AAppleVillager::SetWorkLocation(FVector NewLocation, ATaskVillageLocation* Location)
{
	if (AIController)
	{
		AIController->GetBlackboardComponent()->ClearValue("VibeLocation");
		AIController->GetBlackboardComponent()->SetValueAsVector("TaskLocation", NewLocation);
		ChangeCurrentState(EVillagerState::Working);
	}
}

void AAppleVillager::SetVibeLocation(FVector NewLocation, AVillageVibeLocation* Location)
{
	if (AIController)
	{
		AIController->GetBlackboardComponent()->ClearValue("TaskLocation");
		AIController->GetBlackboardComponent()->SetValueAsVector("VibeLocation", NewLocation);
		ChangeCurrentState(EVillagerState::Vibing);

	}
}

void AAppleVillager::ClearLocations()
{
	AIController->GetBlackboardComponent()->ClearValue("TaskLocation");
	AIController->GetBlackboardComponent()->ClearValue("VibeLocation");

}

void AAppleVillager::ClearEmilia()
{
	AIController->GetBlackboardComponent()->ClearValue("Player");

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

void AAppleVillager::StartFollowTimer()
{
	FTimerHandle FollowEmiliaHandle;
	float TimeVariable = FMath::RandRange(10.f, 35.f);
	ChangeCurrentState(EVillagerState::Following);
	SpawnItemOnHead();
	GetWorld()->GetTimerManager().SetTimer(FollowEmiliaHandle, this, &AAppleVillager::AskForTask, TimeVariable, false);
}

void AAppleVillager::ChangeCurrentState(TEnumAsByte<EVillagerState> NewState)
{
	if (AIController)
	{
		AIController->ChangeVillagerState(NewState);
	}
}

void AAppleVillager::SpawnItemOnHead()
{
	SpawnedItem = GetWorld()->SpawnActor<AActor>(HeadSpawnedItemClass);
	SpawnedItem->SetActorLocation(SpawnLocation->GetComponentLocation());
	SpawnedItem->AttachToComponent(SpawnLocation, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	bHasSpawnedItem = true;
}

TEnumAsByte<EVillagerState> AAppleVillager::GetCurrentState()
{
	return AIController->GetVillagerState();
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
	if (bHasSpawnedItem && EffectToGiveEmilia)
	{
		Player->ApplyEffectToSelf(EffectToGiveEmilia);
		bHasSpawnedItem = false;
		SpawnedItem->Destroy();
	}
}

void AAppleVillager::ResumeVillagerLogic()
{
	if (Manager)
	{
		Manager->ResumeAllApples();
	}
}

void AAppleVillager::AskForTask()
{
	UE_LOG(LogTemp, Warning, TEXT("Getting back to work.."));
	if (Manager)
	{
		ClearEmilia();
		Manager->RemoveEmiliaFollower(this);
		Manager->FindTaskToDo(this);

	}
}

