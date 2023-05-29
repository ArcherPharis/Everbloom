// Fill out your copyright notice in the Description page of Project Settings.


#include "DentonateActor.h"
#include "Components/SphereComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/GameplayAbilityTargetActor.h"

// Sets default values
ADentonateActor::ADentonateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	HitSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Hit Sphere"));
	HitSphere->SetupAttachment(RootComponent);
	HitSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	HitSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

}

// Called when the game starts or when spawned
void ADentonateActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADentonateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<AActor*> ADentonateActor::GetOverlappingActors(AActor* OwnerCharacter)
{
	TArray<AActor*> OverlappingActors;
	HitSphere->GetOverlappingActors(OverlappingActors);
	OverlappingActors.Remove(OwnerCharacter);
	return OverlappingActors;
}

