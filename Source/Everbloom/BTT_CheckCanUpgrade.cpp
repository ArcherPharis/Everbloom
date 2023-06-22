// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_CheckCanUpgrade.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "WorldFlower.h"
#include "Emilia.h"

UBTT_CheckCanUpgrade::UBTT_CheckCanUpgrade()
{
	NodeName = "Can Upgrade Stat?";
}

EBTNodeResult::Type UBTT_CheckCanUpgrade::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AWorldFlower* Pawn = Cast<AWorldFlower>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FlowerKey.SelectedKeyName));

	if (Pawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found the flower."));
		if (AEmilia* Emilia = Cast<AEmilia>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName)))
		{
			int Index = OwnerComp.GetBlackboardComponent()->GetValueAsInt(BlackboardKey.SelectedKeyName);
			bool CanUpgrade;
			Pawn->CheckCanUpgrade(Index, Emilia, CanUpgrade);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanUpgrade", CanUpgrade);
			return EBTNodeResult::Succeeded;
		}

		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
