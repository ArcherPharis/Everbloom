// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_GiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UBTT_GiveAbility : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_GiveAbility();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
};
