// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_UseSpecialAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Dahlia.h"

UBTT_UseSpecialAbility::UBTT_UseSpecialAbility()
{
	NodeName = "Dahlia Random Attack";

}

EBTNodeResult::Type UBTT_UseSpecialAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ADahlia* Dahlia = Cast<ADahlia>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (Dahlia)
	{
		Dahlia->TryUsingRandomSpecialAbility();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
