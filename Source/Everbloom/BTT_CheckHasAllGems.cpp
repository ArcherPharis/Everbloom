// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_CheckHasAllGems.h"
#include "Emilia.h"
#include "InventoryComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_CheckHasAllGems::UBTT_CheckHasAllGems()
{
	NodeName = "Check If Player Has All Gems";
}

EBTNodeResult::Type UBTT_CheckHasAllGems::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEmilia* Emilia = Cast<AEmilia>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName)))
	{
		bool HasAllGems = Emilia->GetInventoryComponent()->ConfirmGemCollection();
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("HasAllGems", HasAllGems);
		return EBTNodeResult::Succeeded;

	}
	return EBTNodeResult::Failed;
}
