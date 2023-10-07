// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "AbilityFlowerItem.h"
#include "Emilia.h"
#include "InventoryComponent.h"
#include "Components/BoxComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	FXSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("FX Location"));
	FXSpawnLocation->SetupAttachment(RootComponent);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Chest Mesh"));
	Mesh->SetupAttachment(RootComponent);
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Box"));
	HitBox->SetupAttachment(RootComponent);
	HitBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);

}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChest::SetChestLockStatus(bool Status)
{
	bIsLocked = Status;
}

void AChest::PlayUnlockEffect()
{
	if(OpenFX)
	UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), OpenFX, FXSpawnLocation->GetComponentLocation(), FXSpawnLocation->GetComponentRotation(), FVector(1.f, 1.f, 1.f));
}

void AChest::InteractWith(AEmilia* Player)
{
	if (bIsLocked)
		return;

	if (!HeldAbilityFlowerClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("No flower in chest!"));
		return;
	}
	UInventoryComponent* PlayerInventoryComponent = Player->GetInventoryComponent();
	if (PlayerInventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got the flower"));
		UAbilityFlowerItem* Flower = NewObject<UAbilityFlowerItem>(Player, HeldAbilityFlowerClass);
		PlayerInventoryComponent->AddAbilityFlower(Flower);
		PlayerLootedChestEvent();
	}
}

