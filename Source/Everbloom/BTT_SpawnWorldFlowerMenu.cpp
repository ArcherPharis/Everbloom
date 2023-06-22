// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_SpawnWorldFlowerMenu.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "WorldFlower.h"
#include "Emilia.h"

UBTT_SpawnWorldFlowerMenu::UBTT_SpawnWorldFlowerMenu()
{
	NodeName = "SpawnWorldFlowerMenu";
}

EBTNodeResult::Type UBTT_SpawnWorldFlowerMenu::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	AWorldFlower* WorldFlower = Cast<AWorldFlower>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (WorldFlower)
	{
		if (AEmilia* Emilia = Cast<AEmilia>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName)))
		{
			WorldFlower->CreateMenuWidget(Emilia);
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;
	}
	return EBTNodeResult::Failed;

}
