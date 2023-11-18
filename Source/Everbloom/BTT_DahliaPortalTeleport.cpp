// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_DahliaPortalTeleport.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MemorySprite.h"

UBTT_DahliaPortalTeleport::UBTT_DahliaPortalTeleport()
{
	NodeName = "Sprite Remove Blocker";
}

EBTNodeResult::Type UBTT_DahliaPortalTeleport::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMemorySprite* MemorySprite = Cast<AMemorySprite>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (MemorySprite)
	{
		MemorySprite->OnRemoveBlocker();
		return EBTNodeResult::Succeeded;

	}
	return EBTNodeResult::Failed;
}
