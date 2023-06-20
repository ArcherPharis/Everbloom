// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogueReplyObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReplyClicked, UDialogueReplyObject*, DialogueClicked);

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UDialogueReplyObject : public UObject
{
	GENERATED_BODY()

public:
	FText GetReply() const { return Reply; }

	void SetReplyText(FText ReplySet);

	FOnReplyClicked OnReplyClicked;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	FText Reply;
	
};
