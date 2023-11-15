// Fill out your copyright notice in the Description page of Project Settings.


#include "CorruptedFlowers.h"
#include "Components/BoxComponent.h"
#include "Emilia.h"
#include "BaseEnemy.h"
#include "WorldFlower.h"
// Sets default values
ACorruptedFlowers::ACorruptedFlowers()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	EnemySpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("EnemySpawnLocation"));
	EnemySpawnLocation->SetupAttachment(RootComponent);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	StartBossFightTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Boss Trigger Box"));
	StartBossFightTriggerBox->SetupAttachment(RootComponent);
	StartBossFightTriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	StartBossFightTriggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void ACorruptedFlowers::BeginPlay()
{
	Super::BeginPlay();
	StartBossFightTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACorruptedFlowers::StartBossFight);
	BlockingVolume->SetActorEnableCollision(false);
}

// Called every frame
void ACorruptedFlowers::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACorruptedFlowers::StartBossFight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Emilia = Cast<AEmilia>(OtherActor))
	{
		ABaseEnemy* EnemySpawned = GetWorld()->SpawnActor<ABaseEnemy>(EnemyToSpawn);
		EnemySpawned->SetActorLocation(EnemySpawnLocation->GetComponentLocation());
		EnemySpawned->SetActorRotation(EnemySpawnLocation->GetComponentRotation());
		EnemySpawned->OnDead.AddDynamic(this, &ACorruptedFlowers::EnemyDied);
		StartBossFightTriggerBox->DestroyComponent();
		BlockingVolume->SetActorEnableCollision(true);
		BlockingField->SetActorHiddenInGame(false);
		
	}
}

void ACorruptedFlowers::EnemyDied()
{
	Flower = GetWorld()->SpawnActor<AWorldFlower>(FlowerToSpawn);
	FVector Offset = FVector(0, 0, 320.f);
	Flower->SetActorLocation(GetActorLocation() + Offset);
	Flower->SetActorRotation(GetActorRotation());
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	BlockingVolume->SetActorEnableCollision(false);
	BlockingField->SetActorHiddenInGame(true);


}

