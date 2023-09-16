// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FlowerWheelReply.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DialogueWidget.h"
#include "Emilia.h"
#include "InventoryComponent.h"

UBTT_FlowerWheelReply::UBTT_FlowerWheelReply()
{
	NodeName = "Flower Reply";
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

//what looks for the answer could just be another widget.
//this widget will look for a maximum of two words.
//choice 1 and 2 are just FTexts. We need to send the reply the player selects
//to said widget, this will determine if they inputted the correct answer or not.
//on two word incanations, we need to give some feedback they got the first one right, or end if wrong

EBTNodeResult::Type UBTT_FlowerWheelReply::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	UDialogueWidget* DialogueWidget = Cast<UDialogueWidget>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	UBTC = &OwnerComp;
	if (DialogueWidget)
	{
		if (AEmilia* Emilia = Cast<AEmilia>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player")))
		{
			bEventReceived = false;
			UInventoryComponent* Inv = Emilia->GetInventoryComponent();
			DialogueWidget->OnReplyFText.RemoveDynamic(this, &UBTT_FlowerWheelReply::AdvanceReply);
			DialogueWidget->OnReplyFText.AddDynamic(this, &UBTT_FlowerWheelReply::AdvanceReply);
			DialogueWidget->ReplyFText(Inv->GetFlowerWords());
			DialogueWidget->AddRepliesToCurrentList(Replies, false);
			return EBTNodeResult::InProgress;
		}
	}

	return EBTNodeResult::Failed;
}

void UBTT_FlowerWheelReply::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (bEventReceived)
	{
		OwnerComp.OnTaskFinished(this, EBTNodeResult::Succeeded);
	}
}

void UBTT_FlowerWheelReply::AdvanceReply(FText Reply)
{
	UBTC->GetBlackboardComponent()->SetValueAsString("Keyword", Reply.ToString());
	bEventReceived = true;
}
