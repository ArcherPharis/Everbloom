// Fill out your copyright notice in the Description page of Project Settings.


#include "RavagerCampfire.h"
#include "Chest.h"

// Sets default values
ARavagerCampfire::ARavagerCampfire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(RootComponent);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ARavagerCampfire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARavagerCampfire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARavagerCampfire::IncrementRavagerCount()
{
	ConnectedRavagers++;
}

void ARavagerCampfire::DecrementRavagerCount()
{
	ConnectedRavagers--;
	if (ConnectedRavagers == 0)
	{
		Chest->SetChestLockStatus(false);
		Chest->PlayUnlockEffect();
	}
}

