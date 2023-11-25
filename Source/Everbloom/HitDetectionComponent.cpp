// Fill out your copyright notice in the Description page of Project Settings.


#include "HitDetectionComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"

UHitDetectionComponent::UHitDetectionComponent()
{
	OnComponentBeginOverlap.AddDynamic(this, &UHitDetectionComponent::Overlapped);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UHitDetectionComponent::Overlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HitActors.Contains(OtherActor))
	{
		return;
	}

	if (OtherActor == GetOwner() || OtherActor == GetOwner()->GetOwner())
	{
		return;
	}
	FGameplayEventData eventData;
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OtherActor->GetName());

	FGameplayAbilityTargetDataHandle TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(OtherActor);
	HitActors.AddUnique(OtherActor);
	eventData.TargetData = TargetData;
	eventData.EventMagnitude = AttackEffectMagnitude;
	eventData.ContextHandle = UAbilitySystemGlobals::Get().AllocGameplayEffectContext();
	FHitResult hitResult = FHitResult{ GetOwner()->GetOwner(), this, GetComponentLocation(), GetComponentVelocity().GetSafeNormal() };
	hitResult.Distance = AttackEffectMagnitude;
	eventData.ContextHandle.AddHitResult(hitResult);
	eventData.ContextHandle.AddInstigator(GetOwner()->GetOwner(), GetOwner()->GetOwner());

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner()->GetOwner(), HitEventTag, eventData);

	const float CooldownDuration = 0.3f;
	GetWorld()->GetTimerManager().SetTimer(HitCooldownTimerHandle, this, &UHitDetectionComponent::ClearHitCooldown, CooldownDuration, false);
}

void UHitDetectionComponent::ClearHitCooldown()
{
	HitActors.Empty();
	GetWorld()->GetTimerManager().ClearTimer(HitCooldownTimerHandle);
}
