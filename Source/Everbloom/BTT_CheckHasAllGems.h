// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_CheckHasAllGems.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UBTT_CheckHasAllGems : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_CheckHasAllGems();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	//FBlackboardKeySelector PlayerKey;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
