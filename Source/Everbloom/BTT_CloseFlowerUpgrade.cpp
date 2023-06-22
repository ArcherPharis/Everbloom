// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_CloseFlowerUpgrade.h"
#include "WorldFlower.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_CloseFlowerUpgrade::UBTT_CloseFlowerUpgrade()
{
	NodeName = "Close Upgrades";
}

EBTNodeResult::Type UBTT_CloseFlowerUpgrade::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AWorldFlower* WorldFlower = Cast<AWorldFlower>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (WorldFlower)
	{

		WorldFlower->CloseMenuWidget();
		return EBTNodeResult::Succeeded;

	}
	return EBTNodeResult::Failed;

}
