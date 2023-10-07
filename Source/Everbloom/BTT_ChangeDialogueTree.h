// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_ChangeDialogueTree.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UBTT_ChangeDialogueTree : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTT_ChangeDialogueTree();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Tree")
	class UBehaviorTree* Tree;

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	

};
