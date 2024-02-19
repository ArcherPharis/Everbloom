// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordPickup.h"
#include "Components/CapsuleComponent.h"
#include "Emilia.h"
#include "InventoryComponent.h"
#include "Weapon.h"

// Sets default values
ASwordPickup::ASwordPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SwordMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	SwordMesh->SetupAttachment(RootComponent);
	DetectionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Detecter"));
	DetectionCapsule->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASwordPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASwordPickup::InteractWith(AEmilia* Player)
{
	Player->GetInventoryComponent()->SpawnNewWeapon(SwordToGive, Player->GetMesh());
	Destroy();
}

// Called every frame
void ASwordPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

