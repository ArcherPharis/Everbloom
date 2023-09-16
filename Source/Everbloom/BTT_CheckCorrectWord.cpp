// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_CheckCorrectWord.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MemorySprite.h"

UBTT_CheckCorrectWord::UBTT_CheckCorrectWord()
{
	NodeName = "Check Correct Word";
}

EBTNodeResult::Type UBTT_CheckCorrectWord::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("SelfActor"));

	if (Actor)
	{
		AMemorySprite* MemSprite = Cast<AMemorySprite>(Actor);
		if (MemSprite->GetKeyword().ToString() == OwnerComp.GetBlackboardComponent()->GetValueAsString(BlackboardKey.SelectedKeyName))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanUpgrade", true);
			return EBTNodeResult::Succeeded;

		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanUpgrade", false);
			return EBTNodeResult::Succeeded;

		}
	}
	return EBTNodeResult::Failed;
}
