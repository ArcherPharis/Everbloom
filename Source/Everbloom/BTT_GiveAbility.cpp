// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_GiveAbility.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MemorySprite.h"
#include "Emilia.h"
#include "InventoryComponent.h"
#include "EBGameplayAbilityBase.h"

UBTT_GiveAbility::UBTT_GiveAbility()
{
	NodeName = "Give Ability";
}

EBTNodeResult::Type UBTT_GiveAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEmilia* Emilia =  Cast<AEmilia>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));
	if (Emilia)
	{
		AMemorySprite* MemSprite = Cast<AMemorySprite>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("SelfActor"));
		UInventoryComponent* InvComp = Emilia->GetInventoryComponent();
		InvComp->GiveStandardMagicToInventory(MemSprite->GetAbility());
		return EBTNodeResult::Succeeded;

	}

	return EBTNodeResult::Failed;
}
