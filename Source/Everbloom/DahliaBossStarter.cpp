// Fill out your copyright notice in the Description page of Project Settings.


#include "DahliaBossStarter.h"
#include "Components/BoxComponent.h"
#include "Dahlia.h"

// Sets default values
ADahliaBossStarter::ADahliaBossStarter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	DahliaSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Location"));
	DahliaSpawnLocation->SetupAttachment(RootComponent);
	BossStartingCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Starting Trigger"));
	BossStartingCollision->SetupAttachment(RootComponent);
	BossStartingCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BossStartingCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void ADahliaBossStarter::BeginPlay()
{
	Super::BeginPlay();
	BossStartingCollision->OnComponentBeginOverlap.AddDynamic(this, &ADahliaBossStarter::Overlapped);
	BlockingVolume->SetActorEnableCollision(false);
}

// Called every frame
void ADahliaBossStarter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADahliaBossStarter::Overlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && DahliaClass)
	{
		Dahlia = GetWorld()->SpawnActor<ADahlia>(DahliaClass);
		Dahlia->SetActorLocation(DahliaSpawnLocation->GetComponentLocation());
		Dahlia->SetActorRotation(DahliaSpawnLocation->GetComponentRotation());
		BlockingVolume->SetActorEnableCollision(true);
		BlockingField->SetActorHiddenInGame(false);
		BossStartingCollision->DestroyComponent();
	}
}

