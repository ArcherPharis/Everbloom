// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "DahliaPortal.generated.h"

UCLASS()
class EVERBLOOM_API ADahliaPortal : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADahliaPortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	virtual void InteractWith(AEmilia* Player);

	UPROPERTY(EditDefaultsOnly, Category = "Sign")
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Sign")
	class UBoxComponent* HitBox;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UDialogueComponent* DialogueComponent;

	UPROPERTY(EditAnywhere, Category = "Campfire")
	class ATargetPoint* RestingPoints;

};
