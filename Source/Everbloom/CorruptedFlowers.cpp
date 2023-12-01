// Fill out your copyright notice in the Description page of Project Settings.


#include "CorruptedFlowers.h"
#include "Components/BoxComponent.h"
#include "Emilia.h"
#include "BaseEnemy.h"
#include "WorldFlower.h"
#include "EBPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "CorruptedFlowers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BossHealthBar.h"
#include "EBAttributeSet.h"

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
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
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
	Emilia = Cast<AEmilia>(OtherActor);
	if (Emilia)
	{
		EnemySpawned = GetWorld()->SpawnActor<ABaseEnemy>(EnemyToSpawn);
		EnemySpawned->SetActorLocation(EnemySpawnLocation->GetComponentLocation());
		EnemySpawned->SetActorRotation(EnemySpawnLocation->GetComponentRotation());
		EnemySpawned->OnDead.AddDynamic(this, &ACorruptedFlowers::EnemyDied);
		StartBossFightTriggerBox->DestroyComponent();
		BlockingVolume->SetActorEnableCollision(true);
		BlockingField->SetActorHiddenInGame(false);
		HealthBarWidget = CreateWidget<UBossHealthBar>(UGameplayStatics::GetPlayerController(this, 0), HealthBarClass);
		HealthBarWidget->AddToViewport();
		HealthBarWidget->SetBossName(BossName);
		EnemySpawned->GetAttributeSet()->OnHealthAttributeChanged.AddDynamic(HealthBarWidget, &UBossHealthBar::SetHealthPercent);
		
	}
}

void ACorruptedFlowers::EnemyDied()
{


	SetFocalActor(EnemySpawned, 1.5f);
	FTimerHandle SpawnNewFlowerHandle;
	GetWorld()->GetTimerManager().SetTimer(SpawnNewFlowerHandle, this, &ACorruptedFlowers::LookAtFlower, 5.0f, false);
	HealthBarWidget->RemoveFromParent();
	BlockingVolume->SetActorEnableCollision(false);
	BlockingField->SetActorHiddenInGame(true);


}

void ACorruptedFlowers::LookAtFlower()
{

	SetFocalActor(this, 1.5f);
	FTimerHandle SpawnNewFlowerHandle;
	GetWorld()->GetTimerManager().SetTimer(SpawnNewFlowerHandle, this, &ACorruptedFlowers::SpawnSavedFlower, 5.0f, false);

}

void ACorruptedFlowers::SpawnSavedFlower()
{
	Flower = GetWorld()->SpawnActor<AWorldFlower>(FlowerToSpawn);
	FVector Offset = FVector(0, 0, 320.f);
	Flower->SetActorLocation(GetActorLocation() + Offset);
	Flower->SetActorRotation(GetActorRotation());
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	NewFlowerEvent();
	FTimerHandle ReturnBackToPlayerHandle;
	GetWorld()->GetTimerManager().SetTimer(ReturnBackToPlayerHandle, this, &ACorruptedFlowers::InteractWithPlayer, 5.0f, false);


}

void ACorruptedFlowers::InteractWithPlayer()
{
	//we need to get WorldFlower to interact with Emilia too.
	AEmilia* Em = Cast<AEmilia>(UGameplayStatics::GetPlayerCharacter(this, 0));
	OnPurified.Broadcast(this);
	Em->OnSentTip.Broadcast(WinTipText);
	Em->Interact(Flower);
	Flower->GiveEmiliaWorldFlowerAbility(Em);
	SetFocalActor(UGameplayStatics::GetPlayerCharacter(this, 0), 2.0f);

}

void ACorruptedFlowers::SetFocalActor(AActor* Target, float Time)
{
	APlayerController* Cont = Cast<APlayerController>(UGameplayStatics::GetPlayerCharacter(this, 0)->GetController());
	if (Cont)
	{
		Cont->SetViewTargetWithBlend(Target, Time);
	}

}

