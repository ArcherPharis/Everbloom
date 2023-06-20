// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_Speak.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UBTT_Speak : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_Speak();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
	FText Text;

	UFUNCTION()
	void AdvanceSpeak();

	bool bEventReceived;

	
};
