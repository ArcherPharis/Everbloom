// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LockOnCapturer.generated.h"

UCLASS()
class EVERBLOOM_API ALockOnCapturer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALockOnCapturer();

	TArray<AActor*> GetAllTargetsInRange();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* SphereNet;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseEnemy> BaseEnemyClass;

	UPROPERTY()
	class AEmilia* Player;

};
