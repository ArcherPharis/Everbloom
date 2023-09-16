// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FailTask.h"

UBTT_FailTask::UBTT_FailTask()
{
	NodeName = "Fail Task";
}

EBTNodeResult::Type UBTT_FailTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Failed;
}
