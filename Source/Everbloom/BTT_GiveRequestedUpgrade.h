// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_GiveRequestedUpgrade.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UBTT_GiveRequestedUpgrade : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_GiveRequestedUpgrade();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector PlayerKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector FlowerKey;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
