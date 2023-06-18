// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldFlower.h"
#include "EBGameplayAbilityBase.h"
#include "Components/CapsuleComponent.h"
#include "Emilia.h"
#include "Blueprint/UserWidget.h"
#include "DialogueComponent.h"


// Sets default values
AWorldFlower::AWorldFlower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	HitCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitCapsule"));
	HitCapsule->SetupAttachment(RootComponent);
	FlowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flower Mesh"));
	FlowerMesh->SetupAttachment(HitCapsule);
	HitCapsule->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
	DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("Dialogue Component"));

}

// Called when the game starts or when spawned
void AWorldFlower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldFlower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldFlower::InteractWith(AEmilia* Player)
{
	//if (MainAbilityClass)
	//{
	//	Player->GiveMainAbility(MainAbilityClass, InputValue);
	//}
	DialogueComponent->CreateDialogueBox(Player);
	
	
}

