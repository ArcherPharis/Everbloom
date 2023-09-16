
#include "BTT_Speak.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DialogueWidget.h"

UBTT_Speak::UBTT_Speak()
{
	NodeName = "Speak";
	INIT_TASK_NODE_NOTIFY_FLAGS();
}

EBTNodeResult::Type UBTT_Speak::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("SelfActor"));
	UDialogueWidget* DialogueWidget =  Cast<UDialogueWidget>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));

	if (DialogueWidget)
	{
		DialogueWidget->Speak(Text);
		DialogueWidget->OnSpeakFinish.RemoveDynamic(this, &UBTT_Speak::AdvanceSpeak);
		DialogueWidget->OnSpeakFinish.AddDynamic(this, &UBTT_Speak::AdvanceSpeak);
		bEventReceived = false;
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;

	
}

void UBTT_Speak::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (bEventReceived)
	{
		
		OwnerComp.OnTaskFinished(this, EBTNodeResult::Succeeded);
		//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void UBTT_Speak::AdvanceSpeak()
{
	
	bEventReceived = true;
}


//UDialogueComponent* DialogueComponent = Cast<UDialogueComponent>(OwnerComp.GetAIOwner()->GetPawn()->GetComponentByClass(UDialogueComponent::StaticClass()));

//
//if (DialogueComponent)
//{
//	OwnerComp.GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, DialogueComponent);
//	return EBTNodeResult::Succeeded;
//}
//return EBTNodeResult::Failed;