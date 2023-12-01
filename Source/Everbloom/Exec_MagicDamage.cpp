// Fill out your copyright notice in the Description page of Project Settings.


#include "Exec_MagicDamage.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BaseCharacter.h"
#include "EBAttributeSet.h"


struct MagicDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Magic);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance);

	MagicDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEBAttributeSet, Health, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEBAttributeSet, Resistance, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEBAttributeSet, Magic, Source, true);

	}
};

static MagicDamageCapture& GetMagicDamageCapture()
{
	static MagicDamageCapture DamageCaptureVar;
	return DamageCaptureVar;
}

UExec_MagicDamage::UExec_MagicDamage()
{
	RelevantAttributesToCapture.Add(GetMagicDamageCapture().HealthDef);
	RelevantAttributesToCapture.Add(GetMagicDamageCapture().MagicDef);
	RelevantAttributesToCapture.Add(GetMagicDamageCapture().ResistanceDef);

}

void UExec_MagicDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const
{
	//out variables
	float OutHealth = 0.0f;

	//capture
	float HealthMagnitude = 0.0f;
	float MagicMagnitude = 0.0f;
	float ResistanceMagnitude = 0.0f;
	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetMagicDamageCapture().HealthDef, FAggregatorEvaluateParameters(), HealthMagnitude);
	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetMagicDamageCapture().MagicDef, FAggregatorEvaluateParameters(), MagicMagnitude);
	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetMagicDamageCapture().ResistanceDef, FAggregatorEvaluateParameters(), ResistanceMagnitude);


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

	if (ResistanceMagnitude > MagicMagnitude)
	{
		OutHealth = HealthMagnitude - 1;

	}
	else
	{
		OutHealth = HealthMagnitude - (MagicMagnitude + Damage - ResistanceMagnitude);

	}

	if (OutHealth <= 0)
	{
		ABaseCharacter* DeadCharacter = Cast<ABaseCharacter>(ExecParams.GetTargetAbilitySystemComponent()->GetOwner());
		if (DeadCharacter)
		{
			//issue is we're not applying the damage from the caster.
			DeadCharacter->SetKiller(Cast<ABaseCharacter>(ExecParams.GetSourceAbilitySystemComponent()->GetOwner()));
		}
	}
	ExecOutputs.AddOutputModifier(FGameplayModifierEvaluatedData(GetMagicDamageCapture().HealthProperty, EGameplayModOp::Override, OutHealth));
}
