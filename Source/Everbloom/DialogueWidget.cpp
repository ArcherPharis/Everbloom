// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"

void UDialogueWidget::InitDialogue(APlayerController* Controller)
{
	Controller->SetInputMode(FInputModeUIOnly());
	Controller->bShowMouseCursor = true;
}
