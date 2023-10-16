// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "ITargetingInterface.h"
#include "BaseEnemy.generated.h"

/**
 * 
 */
UCLASS()
class EVERBLOOM_API ABaseEnemy : public ABaseCharacter, public IITargetingInterface
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Enemy")
	class AWeapon* GetWeapon() const { return Weapon; }

protected:
	virtual void HandleCharacterHealth(float NewValue, float MaxHealth) override;

private:
	virtual void IsTargetable(bool& IsTargetable) override;

	void SpawnWeapon();

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<class AWeapon> WeaponToSpawn;

	AWeapon* Weapon;

	


	
};
