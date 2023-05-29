// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DentonateActor.generated.h"

UCLASS()
class EVERBLOOM_API ADentonateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADentonateActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<AActor*>GetOverlappingActors(AActor* OwnerCharacter);

private:
	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* HitSphere;

};
