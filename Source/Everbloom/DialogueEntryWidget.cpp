// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueEntryWidget.h"
#include "DialogueReplyObject.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UDialogueEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	DialogueButton->OnClicked.AddDynamic(this, &UDialogueEntryWidget::DialogueButtonClicked);
	ReplyObject = Cast<UDialogueReplyObject>(ListItemObject);
	DialogueText->SetText(ReplyObject->GetReply());

}

void UDialogueEntryWidget::DialogueButtonClicked()
{
	ReplyObject->OnReplyClicked.Broadcast(ReplyObject);
}

