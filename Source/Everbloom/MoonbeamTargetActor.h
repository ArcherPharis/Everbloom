// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "MoonbeamTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API AMoonbeamTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AMoonbeamTargetActor();

public:
	UFUNCTION(BlueprintCallable, Category = "Beam")
	FVector GetMoonbeamEndLocation() const;

	UFUNCTION(BlueprintCallable, Category = "Beem")
	float GetMoonbeamLength() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Moonbeam Actor")
	class USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly, Category = "Moonbeam Actor")
	class USpringArmComponent* MoonbeamSpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "Moonbeam Actor")
	class UBoxComponent* TargetArea;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
