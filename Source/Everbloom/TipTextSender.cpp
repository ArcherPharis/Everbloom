// Fill out your copyright notice in the Description page of Project Settings.


#include "TipTextSender.h"
#include "Components/BoxComponent.h"
#include "Emilia.h"

// Sets default values
ATipTextSender::ATipTextSender()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Box"));
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

}

// Called when the game starts or when spawned
void ATipTextSender::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATipTextSender::PlayerOverlapped);
	
}

// Called every frame
void ATipTextSender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATipTextSender::PlayerOverlapped(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEmilia* Emilia = Cast<AEmilia>(OtherActor))
	{
		Emilia->OnSentTip.Broadcast(TextToSend);
		Destroy();
	}
}

