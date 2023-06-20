// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "DialogueEntryWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UDialogueEntryWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject);

	UPROPERTY(meta = (BindWidget))
	class UButton* DialogueButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DialogueText;

	UFUNCTION()
	void DialogueButtonClicked();

	UPROPERTY()
	class UDialogueReplyObject* ReplyObject;
	
};
