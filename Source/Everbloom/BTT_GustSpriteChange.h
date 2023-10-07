// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_GustSpriteChange.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UBTT_GustSpriteChange : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_GustSpriteChange();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Tree")
	class UBehaviorTree* Tree;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
