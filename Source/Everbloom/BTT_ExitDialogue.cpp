// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_ExitDialogue.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DialogueWidget.h"
#include "Emilia.h"

UBTT_ExitDialogue::UBTT_ExitDialogue()
{
	NodeName = "Exit Dialogue";
}

EBTNodeResult::Type UBTT_ExitDialogue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	UDialogueWidget* DialogueWidget = Cast<UDialogueWidget>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (DialogueWidget)
	{
		AEmilia* Em = Cast<AEmilia>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));
		APlayerController* Cont = Cast<APlayerController>(Em->GetController());
		if (Cont)
		{
			Cont->SetViewTargetWithBlend(Em, 0.5f);
		}
		DialogueWidget->Exit();
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
