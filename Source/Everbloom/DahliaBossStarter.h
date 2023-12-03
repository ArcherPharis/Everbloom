// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DahliaBossStarter.generated.h"

UCLASS()
class EVERBLOOM_API ADahliaBossStarter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADahliaBossStarter();



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
	void BossStarted();

private:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* BossStartingCollision;

	UPROPERTY(EditAnywhere)
	class USceneComponent* DahliaSpawnLocation;

	UPROPERTY(EditAnywhere, Category = "Boss Strength Determination")
	TArray<class ACorruptedFlowers*> FlowersInWorld;

	UPROPERTY(EditAnywhere, Category = "Boss Strength Determination")
	TArray<TSubclassOf<class UGameplayEffect>> DahliaStartingStats;

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	TSubclassOf<class ADahlia> DahliaClass;

	UPROPERTY(EditAnywhere, Category = "Boss")
	AActor* BlockingVolume;
	UPROPERTY(EditAnywhere, Category = "Boss")
	AActor* BlockingField;

	ADahlia* Dahlia;

	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	TSubclassOf<class UBossHealthBar> HealthBarClass;
	UPROPERTY(EditDefaultsOnly, Category = "Boss")
	FText BossName;
	UBossHealthBar* HealthBarWidget;

	UFUNCTION()
	void Overlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void FlowerInWorldPurified(ACorruptedFlowers* FlowerPurified);

	void GiveDahliaStats();
};
