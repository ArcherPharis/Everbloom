// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExit);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpeakFinish);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReplyFinish, int, ReplyIndexPicked);


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

private:
	UPROPERTY(meta = (BindWidget))
	class UListView* ReplyListView;
	
};
