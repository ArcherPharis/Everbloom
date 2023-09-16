// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_FailTask.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UBTT_FailTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_FailTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
