// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_UseSpecialAbility.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UBTT_UseSpecialAbility : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_UseSpecialAbility();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
