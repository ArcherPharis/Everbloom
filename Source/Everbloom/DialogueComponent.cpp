// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueComponent.h"
#include "DialogueAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/BrainComponent.h"
#include "DialogueWidget.h"

// Sets default values for this component's properties
UDialogueComponent::UDialogueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogueComponent::BeginPlay()
{
	Super::BeginPlay();
	AICont = GetWorld()->SpawnActor<ADialogueAIController>(ADialogueAIController::StaticClass());

	// ...
	
}


// Called every frame
void UDialogueComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDialogueComponent::OnExit()
{
	AICont->GetBrainComponent()->StopLogic("Dialogue Attempted to exit.");
	DialogueWidget->RemoveFromParent();
	APlayerController* PlayerCont = Cast<APlayerController>(DialogueWidget->GetOwningPlayer());
	PlayerCont->SetInputMode(FInputModeGameOnly());
	PlayerCont->bShowMouseCursor = false;

}

void UDialogueComponent::CreateDialogueBox(APawn* Player)
{
	APlayerController* PlayerCont = Cast<APlayerController>(Player->GetController());
	DialogueWidget = CreateWidget<UDialogueWidget>(PlayerCont, DialogueWidgetClass);
	DialogueWidget->OnExit.AddDynamic(this, &UDialogueComponent::OnExit);
	DialogueWidget->AddToViewport();
	PlayerCont->SetInputMode(FInputModeUIOnly());
	PlayerCont->bShowMouseCursor = true;
	AICont->RunBehaviorTree(DialogueTree);
	UBlackboardComponent* BBoardComp = AICont->GetBlackboardComponent();
	if (BBoardComp)
	{
		BBoardComp->SetValueAsObject("SelfActor", GetOwner());
		BBoardComp->SetValueAsObject("Player", Player);
		BBoardComp->SetValueAsObject(BlackboardWidgetName, DialogueWidget);
	}
}

