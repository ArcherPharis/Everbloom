// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "HitDetectionComponent.h"
#include "BaseCharacter.h"
#include "EBAbilitySystemComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	HitDetectionComp = CreateDefaultSubobject<UHitDetectionComponent>("HitDetectionComp");
	HitDetectionComp->SetupAttachment(WeaponMesh);

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::DisableWeapon()
{
	SetActorHiddenInGame(true);
	HitDetectionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
}

void AWeapon::EnableWeapon()
{
	SetActorHiddenInGame(false);
	HitDetectionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AWeapon::ApplyWeaponEffect(ABaseCharacter* WeaponOwner)
{
	FGameplayEffectSpecHandle Spec = WeaponOwner->GetAbilitySystemComponent()->MakeOutgoingSpec(WeaponEffect, -1, WeaponOwner->GetAbilitySystemComponent()->MakeEffectContext());
	WeaponOwner->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*Spec.Data);

}

void AWeapon::RemoveWeaponEffect(ABaseCharacter* WeaponOwner)
{
	FGameplayEffectSpecHandle Spec = WeaponOwner->GetAbilitySystemComponent()->MakeOutgoingSpec(WeaponRemovalEffect, -1, WeaponOwner->GetAbilitySystemComponent()->MakeEffectContext());
	WeaponOwner->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*Spec.Data);
}

