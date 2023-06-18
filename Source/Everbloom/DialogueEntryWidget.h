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

	UPROPERTY(meta = (BindWidget))
	class UButton* DialogueButton;
	
};
