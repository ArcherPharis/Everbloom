// Fill out your copyright notice in the Description page of Project Settings.


#include "Ravager.h"
#include "EBAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RavagerCampfire.h"

void ARavager::BeginPlay()
{
	Super::BeginPlay();
	if (Campfire)
	{
		AEBAIController* Cont = Cast<AEBAIController>(GetController());
		if (Cont)
		{
			Cont->GetBlackboardComponent()->SetValueAsObject("Campfire", Campfire);
		}
	}
}
