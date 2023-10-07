// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ChangeDialogueTree.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DialogueComponent.h"

UBTT_ChangeDialogueTree::UBTT_ChangeDialogueTree()
{
	NodeName = "Change Dialogue";
}

EBTNodeResult::Type UBTT_ChangeDialogueTree::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* AP = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (AP)
	{
		UDialogueComponent* DC = AP->FindComponentByClass<UDialogueComponent>();
		if (DC)
		{
			DC->ChangeDialogueTree(Tree);
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;

	}
	return EBTNodeResult::Failed;
}
