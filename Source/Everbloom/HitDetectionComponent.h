// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameplayEffectTypes.h"
#include "HitDetectionComponent.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API UHitDetectionComponent : public UCapsuleComponent
{
	GENERATED_BODY()
public:
	UHitDetectionComponent();

	UFUNCTION(BlueprintCallable, Category = "HitDetection")
	FORCEINLINE	void SetEffectMaginitude(float newMag) { AttackEffectMagnitude = newMag; }

private:
	UFUNCTION()
	void Overlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "HitDetection")
	FGameplayTag HitEventTag;

	float AttackEffectMagnitude = 1;

	void ClearHitCooldown();
	FTimerHandle HitCooldownTimerHandle;

	TArray<AActor*> HitActors;
	
};
