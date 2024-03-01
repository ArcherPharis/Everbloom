// Fill out your copyright notice in the Description page of Project Settings.


#include "MemorySprite.h"
#include "DialogueComponent.h"
#include "Components/BoxComponent.h"
#include "Emilia.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InventoryComponent.h"
#include "Weapon.h"

// Sets default values
AMemorySprite::AMemorySprite()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Box"));
	HitBox->SetupAttachment(RootComponent);
	HitBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
	SpriteMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Sprite Mesh"));
	SpriteMesh->SetupAttachment(HitBox);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("Dialogue Component"));

}

// Called when the game starts or when spawned
void AMemorySprite::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMemorySprite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMemorySprite::InteractWith(AEmilia* Player)
{
	APlayerController* Cont = Cast<APlayerController>(Player->GetController());
	if (Cont)
	{
		Cont->SetViewTarget(this);
		Player->SetActorHiddenInGame(true);
		Player->GetInventoryComponent()->GetCurrentWeapon()->SetActorHiddenInGame(true);
		OnInteracted();
	}
	DialogueComponent->CreateDialogueBox(Player);
	
}

