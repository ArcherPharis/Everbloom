// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_EnemyAttack.h"
#include "BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_EnemyAttack::UBTT_EnemyAttack()
{
	NodeName = "Enemy Attack";
}

EBTNodeResult::Type UBTT_EnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ABaseEnemy* Enemy = Cast<ABaseEnemy>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	if (Enemy)
	{
		Enemy->UseMeleeAbility();
	}
	return EBTNodeResult::Succeeded;

}
