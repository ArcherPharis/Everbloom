// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Weapon.h"
#include "EBAbilitySystemComponent.h"
#include "Emilia.h"
#include "InventoryComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void ABaseEnemy::IsTargetable(bool& IsTargetable)
{
	IsTargetable = true;
}

void ABaseEnemy::SpawnWeapon()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponToSpawn, SpawnParams);
	FAttachmentTransformRules AttachRules{ EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true };
	Weapon->AttachToComponent(GetMesh(), AttachRules, Weapon->GetAttachmentSocketName());
	Weapon->SetOwner(this);
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (WeaponToSpawn)
	{
		SpawnWeapon();

	}
	GiveAbility(MeleeAbility);
}

void ABaseEnemy::UseMeleeAbility()
{
	GetAbilitySystemComponent()->TryActivateAbilityByClass(MeleeAbility);
}

void ABaseEnemy::HandleCharacterHealth(float NewValue, float MaxHealth, float OldHealth)
{
	Super::HandleCharacterHealth(NewValue, MaxHealth, OldHealth);
	if (NewValue == 0)
	{
		AAIController* Cont = Cast<AAIController>(GetOwner());
		if (Cont)
		{
			Cont->GetBrainComponent()->StopLogic("cuz he ded");
		}

		if (GetKiller())
		{
			if (AEmilia* Player = Cast<AEmilia>(GetKiller()))
			{
				Player->CheckToUnlock(this);
				Player->GetInventoryComponent()->SetLifedewAmount(LifedewRewardAmount);
			}
		}
		GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	}
	else
	{
		if(GetFlinchMontage())
		GetMesh()->GetAnimInstance()->Montage_Play(GetFlinchMontage());
	}

	//AAIController* AIC = GetController<AAIController>();
	//if (AIC)
	//{
	//	AEmilia* Player = Cast<AEmilia>(UGameplayStatics::GetPlayerCharacter(this, 0));
	//	AIC->GetBlackboardComponent()->SetValueAsObject("Target", Player);
	//}
}
