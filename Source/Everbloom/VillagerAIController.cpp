// Fill out your copyright notice in the Description page of Project Settings.


#include "VillagerAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AppleVillager.h"
#include "ApplePeopleVillageManager.h"

AVillagerAIController::AVillagerAIController()
{
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("PerceptionComp");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	if (SightConfig)
	{
		PerceptionComp->ConfigureSense(*SightConfig);
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AVillagerAIController::PerceptionUpdated);
	}
}

void AVillagerAIController::ChangeVillagerState(TEnumAsByte<EVillagerState> NewState)
{
	CurrentVillagerState = NewState;
}

void AVillagerAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
	VillagePawn = Cast<AAppleVillager>(GetPawn());
}

void AVillagerAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	IGenericTeamAgentInterface* pawnInterface = Cast<IGenericTeamAgentInterface>(InPawn);
	if (pawnInterface)
	{
		TeamID = pawnInterface->GetGenericTeamId();
	}
}

ETeamAttitude::Type AVillagerAIController::GetTeamAttitudeTowards(const AActor& Other) const
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

void AVillagerAIController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && CurrentVillagerState == EVillagerState::Vibing)
	{
		//we need to ask the manager if we can set this or not as well if we are in the correct state.
		if (VillagePawn->GetManager()->CheckIfCanFollowEmilia(VillagePawn))
		{
			GetBlackboardComponent()->SetValueAsObject("Player", Actor);
		}
	}
	else
	{
		auto PerceptionInfo = PerceptionComp->GetActorInfo(*Actor);
		if (!PerceptionInfo->HasAnyCurrentStimulus())
		{
			

		}
	}
}
