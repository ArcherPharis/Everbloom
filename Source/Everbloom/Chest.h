// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "Chest.generated.h"

UCLASS()
class EVERBLOOM_API AChest : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetChestLockStatus(bool Status);

	void PlayUnlockEffect();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayerLootedChestEvent();

private:
	virtual void InteractWith(AEmilia* Player);

	UPROPERTY(EditDefaultsOnly, Category = "Chest")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Chest")
	USceneComponent* FXSpawnLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Chest")
	TSubclassOf<class UAbilityFlowerItem> HeldAbilityFlowerClass;

	UPROPERTY(VisibleAnywhere, Category = "Chest")
	bool bIsLocked = true;

	UPROPERTY(EditDefaultsOnly, Category = "Chest")
	class UBoxComponent* HitBox;

	UPROPERTY(EditDefaultsOnly, Category = "Quake")
	class UNiagaraSystem* OpenFX;

};
