// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_SpawnWorldFlowerMenu.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UBTT_SpawnWorldFlowerMenu : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_SpawnWorldFlowerMenu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector PlayerKey;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
