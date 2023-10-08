// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "AIController.h"
#include "BrainComponent.h"

void ABaseEnemy::IsTargetable(bool& IsTargetable)
{
	IsTargetable = true;
}

void ABaseEnemy::HandleCharacterHealth(float NewValue, float MaxHealth)
{
	Super::HandleCharacterHealth(NewValue, MaxHealth);
	if (NewValue == 0)
	{
		AAIController* Cont = Cast<AAIController>(GetOwner());
		if (Cont)
		{
			Cont->GetBrainComponent()->StopLogic("cuz he ded");
		}
	}
}
