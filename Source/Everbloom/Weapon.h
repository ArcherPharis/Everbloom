// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class EVERBLOOM_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FName GetAttachmentSocketName() const { return WeaponSocketName; }

	void DisableWeapon();
	void EnableWeapon();

	void ApplyWeaponEffect(class ABaseCharacter* WeaponOwner);
	void RemoveWeaponEffect(ABaseCharacter* WeaponOwner);

	UTexture2D* GetWeaponIcon() const { return WeaponIcon; }
	FText GetWeaponName() const { return WeaponName; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UTexture2D* WeaponIcon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FText WeaponName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponSocketName;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class UGameplayEffect> WeaponEffect;
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class UGameplayEffect> WeaponRemovalEffect;

	UPROPERTY(VisibleDefaultsOnly, Category = "GameplayAbility")
	class UHitDetectionComponent* HitDetectionComp;

};
