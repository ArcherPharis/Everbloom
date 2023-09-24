// Fill out your copyright notice in the Description page of Project Settings.


#include "DahliaPortal.h"
#include "DialogueComponent.h"
#include "Components/BoxComponent.h"
#include "Emilia.h"
#include "Engine/TargetPoint.h"


// Sets default values
ADahliaPortal::ADahliaPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Box"));
	HitBox->SetupAttachment(RootComponent);
	HitBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	DoorMesh->SetupAttachment(HitBox);
	DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("Dialogue Component"));

}

// Called when the game starts or when spawned
void ADahliaPortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADahliaPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADahliaPortal::InteractWith(AEmilia* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("IS THIS WORKING"));
	if (Player)
	{
		Player->SetActorLocation(RestingPoints->GetActorLocation());
		Player->SetActorRotation(RestingPoints->GetActorRotation());
	}

	//DialogueComponent->CreateDialogueBox(Player);
}

