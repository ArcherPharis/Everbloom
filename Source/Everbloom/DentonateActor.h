// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "DentonateActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExplosion, FGameplayAbilityTargetDataHandle, DataHandle);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorTouchedSphere, FGameplayAbilityTargetDataHandle, ActorOverlapped);


UCLASS()
class EVERBLOOM_API ADentonateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADentonateActor();

	FOnExplosion OnExplosion;
	FOnActorTouchedSphere OnActorTouchedSphere;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<AActor*>GetOverlappingActors(AActor* OwnerCharacter);

	void SendOverlappingActors(AActor* OwningCharacter);

private:
	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* HitSphere;


	UPROPERTY(EditDefaultsOnly)
	bool bGrabberSphere{ false };
};

