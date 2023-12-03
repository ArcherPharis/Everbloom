// Fill out your copyright notice in the Description page of Project Settings.


#include "DahliaBossStarter.h"
#include "Components/BoxComponent.h"
#include "Dahlia.h"
#include "CorruptedFlowers.h"
#include "BossHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "EBAttributeSet.h"

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

	for (ACorruptedFlowers* Flower : FlowersInWorld)
	{
		Flower->OnPurified.AddDynamic(this, &ADahliaBossStarter::FlowerInWorldPurified);
	}
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
		GiveDahliaStats();
		BossStarted();
		HealthBarWidget = CreateWidget<UBossHealthBar>(UGameplayStatics::GetPlayerController(this, 0), HealthBarClass);
		HealthBarWidget->AddToViewport();
		HealthBarWidget->SetBossName(BossName);
		Dahlia->GetAttributeSet()->OnHealthAttributeChanged.AddDynamic(HealthBarWidget, &UBossHealthBar::SetHealthPercent);
	}
}

void ADahliaBossStarter::FlowerInWorldPurified(ACorruptedFlowers* FlowerPurified)
{
	FlowersInWorld.Remove(FlowerPurified);
}

void ADahliaBossStarter::GiveDahliaStats()
{
	if (Dahlia)
	{
		Dahlia->ApplyEffectToSelf(DahliaStartingStats[FlowersInWorld.Num()]);
	}
}

