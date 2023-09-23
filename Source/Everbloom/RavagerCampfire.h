// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RavagerCampfire.generated.h"

UCLASS()
class EVERBLOOM_API ARavagerCampfire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARavagerCampfire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Campfire")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Campfire")
	TArray<class ATargetPoint*> RestingPoints;

};
