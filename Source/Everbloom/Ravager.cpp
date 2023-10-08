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
			Campfire->IncrementRavagerCount();
			Cont->GetBlackboardComponent()->SetValueAsObject("Campfire", Campfire);
		}
	}
}

void ARavager::HandleCharacterHealth(float NewValue, float MaxHealth)
{
	Super::HandleCharacterHealth(NewValue, MaxHealth);
	if (NewValue == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("I'm dead!"));
		if (Campfire)
		{
			Campfire->DecrementRavagerCount();

		}
	}
}
