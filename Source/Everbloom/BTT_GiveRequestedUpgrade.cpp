// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_GiveRequestedUpgrade.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "WorldFlower.h"
#include "Emilia.h"

UBTT_GiveRequestedUpgrade::UBTT_GiveRequestedUpgrade()
{
	NodeName = "Give Upgrade";
}

EBTNodeResult::Type UBTT_GiveRequestedUpgrade::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AWorldFlower* Pawn = Cast<AWorldFlower>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FlowerKey.SelectedKeyName));

	if (Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found the flower."));
		if (AEmilia* Emilia = Cast<AEmilia>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName)))
		{
			Pawn->GiveUpgrade(OwnerComp.GetBlackboardComponent()->GetValueAsInt(BlackboardKey.SelectedKeyName), Emilia);
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;

	}
	return EBTNodeResult::Failed;

}
