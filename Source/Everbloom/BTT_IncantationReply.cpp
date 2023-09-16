// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_IncantationReply.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MemorySprite.h"
#include "DialogueWidget.h"

UBTT_IncantationReply::UBTT_IncantationReply()
{
	NodeName = "Incantation Speak";
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UBTT_IncantationReply::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("SelfActor"));
	UDialogueWidget* DialogueWidget = Cast<UDialogueWidget>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));

	if (DialogueWidget && Actor)
	{
		AMemorySprite* MemSprite = Cast<AMemorySprite>(Actor);
		OwnerComp.GetBlackboardComponent()->SetValueAsString("Incantation", MemSprite->GetIncantation().ToString());
		DialogueWidget->Speak(MemSprite->GetIncantation());
		DialogueWidget->OnSpeakFinish.RemoveDynamic(this, &UBTT_IncantationReply::AdvanceSpeak);
		DialogueWidget->OnSpeakFinish.AddDynamic(this, &UBTT_IncantationReply::AdvanceSpeak);
		bEventReceived = false;
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;

}

void UBTT_IncantationReply::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (bEventReceived)
	{
		OwnerComp.OnTaskFinished(this, EBTNodeResult::Succeeded);
	}
}

void UBTT_IncantationReply::AdvanceSpeak()
{
	bEventReceived = true;
}
