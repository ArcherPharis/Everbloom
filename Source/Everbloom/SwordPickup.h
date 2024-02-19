// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "SwordPickup.generated.h"

UCLASS()
class EVERBLOOM_API ASwordPickup : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwordPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InteractWith(AEmilia* Player);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "SwordPickup")
	USkeletalMeshComponent* SwordMesh;

	UPROPERTY(EditAnywhere, Category = "SwordPickup")
	class UCapsuleComponent* DetectionCapsule;

	UPROPERTY(EditDefaultsOnly, Category = "SwordPickup")
	TSubclassOf<class AWeapon> SwordToGive;



};
