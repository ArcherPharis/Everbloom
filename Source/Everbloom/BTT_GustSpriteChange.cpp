// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_GustSpriteChange.h"
#include "MemorySprite.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DialogueComponent.h"

UBTT_GustSpriteChange::UBTT_GustSpriteChange()
{
	NodeName = "Gust Sprite Dialogue Change";
}

EBTNodeResult::Type UBTT_GustSpriteChange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMemorySprite* AP = Cast<AMemorySprite>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (AP)
	{
		UDialogueComponent* DC = AP->FindComponentByClass<UDialogueComponent>();
		if (DC)
		{
			AP->OnDialogueChanged();
			DC->ChangeDialogueTree(Tree);
			return EBTNodeResult::Succeeded;
		}
		return EBTNodeResult::Failed;

	}
	return EBTNodeResult::Failed;
}
