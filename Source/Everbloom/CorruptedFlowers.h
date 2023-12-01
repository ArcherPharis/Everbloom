// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CorruptedFlowers.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPurified, ACorruptedFlowers*, Flower);

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

	UFUNCTION(BlueprintImplementableEvent, Category = "Corrupted Flower")
	void NewFlowerEvent();

	FOnPurified OnPurified;
private:

	UPROPERTY(EditAnywhere, Category = "CorruptedFlower")
	USceneComponent* EnemySpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "CorruptedFlower")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "CorruptedFlower")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "CorruptedFlower")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "CorruptedFlower")
	class UBoxComponent* StartBossFightTriggerBox;

	UPROPERTY(EditAnywhere, Category = "CorruptedFlower")
	TSubclassOf<class ABaseEnemy> EnemyToSpawn;

	UPROPERTY(EditAnywhere, Category = "CorruptedFlower")
	TSubclassOf<class AWorldFlower> FlowerToSpawn;
	AWorldFlower* Flower;

	UPROPERTY(EditAnywhere, Category = "CorruptedFlower")
	FText WinTipText;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UBossHealthBar> HealthBarClass;
	UPROPERTY(EditDefaultsOnly)
	FText BossName;


	UBossHealthBar* HealthBarWidget;

	UPROPERTY(EditAnywhere, Category = "CorruptedFlower")
	AActor* BlockingVolume;
	UPROPERTY(EditAnywhere, Category = "CorruptedFlower")
	AActor* BlockingField;

	UFUNCTION()
	void StartBossFight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EnemyDied();

	void LookAtFlower();

	void SpawnSavedFlower();

	void InteractWithPlayer();

	class AEmilia* Emilia;
	ABaseEnemy* EnemySpawned;

	void SetFocalActor(AActor* Target, float Time);

};
