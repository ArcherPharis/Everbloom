// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

UCLASS()
class EVERBLOOM_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetHomingTarget(AActor* PotentialTarget, TSubclassOf<class UGameplayEffect> GPE);

	void SetProjectileVelocity(FVector CameraLocation, TSubclassOf<class UGameplayEffect> GPE);

	void SetCaster(AActor* Caster);

private:

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* SphereDetection;

	UPROPERTY(EditDefaultsOnly)
	class UNiagaraComponent* ProjectileParticle;

	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly)
	bool bIsPersistentProjectile = false;

	UFUNCTION()
	void OnImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	TSubclassOf<class UGameplayEffect> EffectToApply;
};
