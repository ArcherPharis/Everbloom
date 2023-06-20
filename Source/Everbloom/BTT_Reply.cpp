// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Reply.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DialogueWidget.h"

UBTT_Reply::UBTT_Reply()
{
	NodeName = "Reply";
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UBTT_Reply::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();
	UDialogueWidget* DialogueWidget = Cast<UDialogueWidget>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	UBTC = &OwnerComp;
	if (DialogueWidget)
	{
		bEventReceived = false;

		DialogueWidget->OnReplyFinish.RemoveDynamic(this, &UBTT_Reply::AdvanceReply);
		DialogueWidget->OnReplyFinish.AddDynamic(this, &UBTT_Reply::AdvanceReply);
		DialogueWidget->Reply(Replies);
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

void UBTT_Reply::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (bEventReceived)
	{
		OwnerComp.OnTaskFinished(this, EBTNodeResult::Succeeded);
	}
}

void UBTT_Reply::AdvanceReply(int ReplyInd)
{
	UBTC->GetBlackboardComponent()->SetValueAsInt(ReplyIndex.SelectedKeyName, ReplyInd);
	bEventReceived = true;
}
