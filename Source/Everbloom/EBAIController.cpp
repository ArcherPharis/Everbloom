// Fill out your copyright notice in the Description page of Project Settings.


#include "EBAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

AEBAIController::AEBAIController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	if (SightConfig)
	{
		PerceptionComp->ConfigureSense(*SightConfig);
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEBAIController::PerceptionUpdated);
	}
}

void AEBAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void AEBAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	IGenericTeamAgentInterface* pawnInterface = Cast<IGenericTeamAgentInterface>(InPawn);
	if (pawnInterface)
	{
		TeamID = pawnInterface->GetGenericTeamId();
	}
}

ETeamAttitude::Type AEBAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* pawn = Cast<APawn>(&Other);

	if (!pawn)
		return ETeamAttitude::Neutral;

	auto pTI = Cast<IGenericTeamAgentInterface>(&Other);
	class IGenericTeamAgentInterface* bTI = Cast<IGenericTeamAgentInterface>(pawn->GetController());
	if (bTI == nullptr && pTI == nullptr)
		return ETeamAttitude::Neutral;


	FGenericTeamId otherID = NULL;
	if (bTI != nullptr)
	{
		otherID = bTI->GetGenericTeamId();
	}
	else if (pTI != nullptr)
	{
		otherID = pTI->GetGenericTeamId();
	}

	if (otherID == 20)
	{
		return ETeamAttitude::Neutral;
	}
	else if (otherID == TeamID)
	{
		return ETeamAttitude::Friendly;
	}
	else
	{
		return ETeamAttitude::Hostile;
	}
}

void AEBAIController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{

		GetBlackboardComponent()->SetValueAsObject(TargetBlackboardKeyName, Actor);
	}
	else
	{
		auto PerceptionInfo = PerceptionComp->GetActorInfo(*Actor);
		if (!PerceptionInfo->HasAnyCurrentStimulus())
		{
			UE_LOG(LogTemp, Warning, TEXT("I lost track of: %s"), *Actor->GetName());
			GetBlackboardComponent()->ClearValue(TargetBlackboardKeyName);
			GetBlackboardComponent()->SetValueAsVector(LastSeenKeyName, Actor->GetActorLocation());
		}
	}
}
