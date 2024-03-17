// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_GiveBloomsword.h"
#include "Emilia.h"
#include "InventoryComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_GiveBloomsword::UBTT_GiveBloomsword()
{
	NodeName = "Give Emilia Bloomsword";
}

EBTNodeResult::Type UBTT_GiveBloomsword::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEmilia* Emilia = Cast<AEmilia>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName)))
	{
		Emilia->GetInventoryComponent()->GiveBloomsword();
		return EBTNodeResult::Succeeded;

	}
	return EBTNodeResult::Failed;
}
