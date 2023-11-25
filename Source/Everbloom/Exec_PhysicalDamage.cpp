// Fill out your copyright notice in the Description page of Project Settings.


#include "Exec_PhysicalDamage.h"
#include "EBAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BaseCharacter.h"

struct DamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);

	DamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEBAttributeSet, Health, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEBAttributeSet, Defense, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEBAttributeSet, Strength, Source, true);
	}

};
static DamageCapture& GetDamageCapture()
{
	static DamageCapture DamageCaptureVar;
	return DamageCaptureVar;
}



UExec_PhysicalDamage::UExec_PhysicalDamage()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().HealthDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().DefenseDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().StrengthDef);
}

void UExec_PhysicalDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const
{

	//out variables
	float OutHealth = 0.0f;

	//capture
	float HealthMagnitude = 0.0f;
	float AttackMagnitude = 0.0f;
	float DefenseMagnitude = 0.0f;
	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().HealthDef, FAggregatorEvaluateParameters(), HealthMagnitude);
	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().DefenseDef, FAggregatorEvaluateParameters(), DefenseMagnitude);
	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().StrengthDef, FAggregatorEvaluateParameters(), AttackMagnitude);


	UAbilitySystemComponent* TargetAbilitySystem = ExecParams.GetTargetAbilitySystemComponent();
	if (TargetAbilitySystem)
	{
		FGameplayTag MyTagToCheck = FGameplayTag::RequestGameplayTag("Status.Blocking");
		bool bIsBlocking = TargetAbilitySystem->HasMatchingGameplayTag(MyTagToCheck);
		if (bIsBlocking)
		{
			FGameplayEventData EventData;
			EventData.Instigator = ExecParams.GetSourceAbilitySystemComponent()->GetOwner();
			TargetAbilitySystem->HandleGameplayEvent(EventTag, &EventData);
			return;
		}
	}

	if (DefenseMagnitude > AttackMagnitude)
	{
		OutHealth = HealthMagnitude - 1;

	}
	else
	{
		OutHealth = HealthMagnitude - (AttackMagnitude - DefenseMagnitude);

	}

	if (OutHealth <= 0)
	{
		ABaseCharacter* DeadCharacter = Cast<ABaseCharacter>(ExecParams.GetTargetAbilitySystemComponent()->GetOwner());
		if (DeadCharacter)
		{
			DeadCharacter->SetKiller(Cast<ABaseCharacter>(ExecParams.GetSourceAbilitySystemComponent()->GetOwner()));
		}
	}
	ExecOutputs.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCapture().HealthProperty, EGameplayModOp::Override, OutHealth));
}
