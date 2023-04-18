// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class AAbilityFlower;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewAbilityFlowerObtained, AAbilityFlower*, Flower);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVERBLOOM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	void AddAbilityFlower(AAbilityFlower* FlowerToAdd);
	FOnNewAbilityFlowerObtained OnNewAbilityFlowerObtained;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitializeInventory(USceneComponent* CompToAttach);

private:
	
	UPROPERTY(VisibleAnywhere, Category = "Ability Flowers")
	TArray<AAbilityFlower*> FlowersObtained;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeapon> InitialWeaponClass;

	UPROPERTY()
	TArray<AWeapon*> Weapons;

	UPROPERTY()
	AWeapon* CurrentWeapon;

		
};
