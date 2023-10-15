// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CorruptedFlowers.generated.h"

UCLASS()
class EVERBLOOM_API ACorruptedFlowers : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACorruptedFlowers();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "CorruptedFlower")
	USceneComponent* EnemySpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "CorruptedFlower")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "CorruptedFlower")
	class UBoxComponent* StartBossFightTriggerBox;

	UPROPERTY(EditAnywhere, Category = "CorruptedFlower")
	TSubclassOf<class ABaseEnemy> EnemyToSpawn;

	UPROPERTY(EditAnywhere, Category = "CorruptedFlower")
	TSubclassOf<class AWorldFlower> FlowerToSpawn;

	UFUNCTION()
	void StartBossFight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
