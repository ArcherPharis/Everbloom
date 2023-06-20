// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"
#include "Components/TextBlock.h"
#include "Components/SizeBox.h"
#include "DialogueReplyObject.h"
#include "Components/ListView.h"
#include "DialogueReplyObject.h"

void UDialogueWidget::InitDialogue(APlayerController* Controller)
{
	Controller->SetInputMode(FInputModeUIOnly());
	Controller->bShowMouseCursor = true;
}

void UDialogueWidget::Speak(FText Text)
{
	SpeakText->SetText(Text);
	SetDialogueState(EDialogueState::Speak);
}

void UDialogueWidget::Reply(TArray<FText> Replies)
{
	ReplyListView->ClearListItems();

	for (FText Reply : Replies)
	{
		UDialogueReplyObject* ReplyObject = NewObject<UDialogueReplyObject>(ReplyObjectClass);
		ReplyObject->OnReplyClicked.AddDynamic(this, &UDialogueWidget::ReplyClicked);
		ReplyObject->SetReplyText(Reply);
		ReplyListView->AddItem(ReplyObject);
		SetDialogueState(EDialogueState::Reply);
	}
}

void UDialogueWidget::Exit()
{
	OnExit.Broadcast();
}

FReply UDialogueWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	switch (dialogueState)
	{
		case EDialogueState::Speak:
			if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
			{
				
				OnSpeakFinish.Broadcast();
			}
			break;
		case EDialogueState::Reply: break;
		default: break;
	}

	return Reply;
}

void UDialogueWidget::SetDialogueState(EDialogueState DialState)
{
	dialogueState = DialState;
	switch (dialogueState)
	{
		case EDialogueState::Speak:
			ReplySizeBox->SetVisibility(ESlateVisibility::Collapsed);
			SpeakSizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			break;
		case EDialogueState::Reply: 
			ReplySizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			SpeakSizeBox->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			break;
		default: break;
	}
}

void UDialogueWidget::ReplyClicked(UDialogueReplyObject* ReplyClicked)
{
	OnReplyFinish.Broadcast(ReplyListView->GetIndexForItem(ReplyClicked));
}
