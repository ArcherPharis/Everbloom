// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UAbilityFlowerItem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewAbilityFlowerObtained, UAbilityFlowerItem*, Flower);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVERBLOOM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	void AddAbilityFlower(UAbilityFlowerItem* FlowerToAdd);
	FOnNewAbilityFlowerObtained OnNewAbilityFlowerObtained;

	void GiveNewMagic(class UEBGameplayAbilityBase* NewAbility);
	float GetCurrentWeaponDamage() const;

	UFUNCTION(BlueprintPure, Category = "InventoryComp")
	class AWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

	int GetLifedews() const { return Lifedew; }
	void SetLifedewAmount(int Amount);

	TArray<UAbilityFlowerItem*> GetFlowersObtained() const { return FlowersObtained; }

	UEBGameplayAbilityBase* GetCurrentMagic() const { return CurrentMagic; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitializeInventory(USceneComponent* CompToAttach);

	bool CheckIfFlowerExistsInInventory(UAbilityFlowerItem* FlowerToCheck);

private:
	void GiveStarterMagic();

	UPROPERTY(VisibleAnywhere, Category = "Ability Flowers")
	TArray<UAbilityFlowerItem*> FlowersObtained;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWeapon> InitialWeaponClass;

	UPROPERTY(EditDefaultsOnly)
	int Lifedew = 0;

	int MaxLifedewAmount = 9999;

	UPROPERTY()
	TArray<AWeapon*> Weapons;
	UPROPERTY(VisibleAnywhere, Category = "Abilities")
	TArray<class UEBGameplayAbilityBase*> Magic;

	UPROPERTY(VisibleAnywhere, Category = "Ability Flowers")
	TArray<TSubclassOf<class UEBGameplayAbilityBase>> ObtainedFlowerAbilities;
	UPROPERTY(EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UEBGameplayAbilityBase> StarterWindMagicClass;
	UPROPERTY(VisibleAnywhere)
	AWeapon* CurrentWeapon;
	UPROPERTY(VisibleAnywhere, Category = "Abilities")
	UEBGameplayAbilityBase* CurrentMagic;

	
		
};
