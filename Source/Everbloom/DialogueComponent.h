// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueExit);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVERBLOOM_API UDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueComponent();
	FOnDialogueExit OnDialogueExit;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnExit();

	void CreateDialogueBox(APawn* Player);

	UFUNCTION(BlueprintCallable, Category = "DialogueComponent")
	void ChangeDialogueTree(class UBehaviorTree* NewTree);

	class UDialogueWidget* GetDialogueWidget() const { return DialogueWidget; }
private:
	class ADialogueAIController* AICont;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;

	UPROPERTY()
	UDialogueWidget* DialogueWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UBehaviorTree* DialogueTree;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	FName BlackboardWidgetName {"DialogueWidget"};

		
};
