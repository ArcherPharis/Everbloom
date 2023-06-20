// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_Reply.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UBTT_Reply : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UBTT_Reply();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector ReplyIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	TArray<FText> Replies;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;


	UFUNCTION()
	void AdvanceReply(int ReplyInd);

	bool bEventReceived;

	UBehaviorTreeComponent* UBTC;
	
};
