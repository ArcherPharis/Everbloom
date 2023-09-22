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
}

void AEBAIController::OnPossess(APawn* InPawn)
{
}

void AEBAIController::PerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
}
