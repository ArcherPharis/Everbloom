// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpeakFinish);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReplyFinish, int, ReplyIndexPicked);

UENUM()
enum EDialogueState
{
	Speak,
	Reply
};


/**
 * 
 */
UCLASS()
class EVERBLOOM_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnExit OnExit;
	FOnSpeakFinish OnSpeakFinish;
	FOnReplyFinish OnReplyFinish;

	void InitDialogue(APlayerController* Controller);

	void Speak(FText Text);
	void Reply(TArray<FText> Replies);
	void Exit();

private:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(meta = (BindWidget))
	class UListView* ReplyListView;

	UPROPERTY()
	TEnumAsByte<EDialogueState> dialogueState;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SpeakText;
	UPROPERTY(meta = (BindWidget))
	class USizeBox* SpeakSizeBox;
	UPROPERTY(meta = (BindWidget))
	class USizeBox* ReplySizeBox;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TSubclassOf<class UDialogueReplyObject> ReplyObjectClass;

	void SetDialogueState(EDialogueState DialState);

	UFUNCTION()
	void ReplyClicked(class UDialogueReplyObject* ReplyClicked);
	
};
