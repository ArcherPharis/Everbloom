// Fill out your copyright notice in the Description page of Project Settings.


#include "LockOnCapturer.h"
#include "BaseEnemy.h"
#include "Emilia.h"
#include "ITargetingInterface.h"
#include "Components/SphereComponent.h"

// Sets default values
ALockOnCapturer::ALockOnCapturer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SphereNet = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Net"));
	SphereNet->SetupAttachment(RootComponent);

}

TArray<AActor*> ALockOnCapturer::GetAllTargetsInRange()
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors, BaseEnemyClass);
	TArray<AActor*> TargetsInRange;


	for (AActor* Actor : Actors)
	{
		TargetsInRange.AddUnique(Actor);

	}


	return TargetsInRange;
}

// Called when the game starts or when spawned
void ALockOnCapturer::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<AEmilia>(GetOwner());
	
}

// Called every frame
void ALockOnCapturer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

