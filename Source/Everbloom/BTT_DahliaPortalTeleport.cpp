// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_DahliaPortalTeleport.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DahliaPortal.h"

UBTT_DahliaPortalTeleport::UBTT_DahliaPortalTeleport()
{
	NodeName = "Teleport Emilia";
}

EBTNodeResult::Type UBTT_DahliaPortalTeleport::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ADahliaPortal* Portal = Cast<ADahliaPortal>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (Portal)
	{
		Portal->TeleportEmilia();
	}
	return EBTNodeResult::Succeeded;
}
