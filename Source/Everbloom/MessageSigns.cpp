// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageSigns.h"
#include "DialogueComponent.h"
#include "Components/BoxComponent.h"
#include "Emilia.h"

// Sets default values
AMessageSigns::AMessageSigns()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Box"));
	HitBox->SetupAttachment(RootComponent);
	HitBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
	SignMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	SignMesh->SetupAttachment(HitBox);
	DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("Dialogue Component"));
}

// Called when the game starts or when spawned
void AMessageSigns::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMessageSigns::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMessageSigns::InteractWith(AEmilia* Player)
{
	DialogueComponent->CreateDialogueBox(Player);
}

