// Fill out your copyright notice in the Description page of Project Settings.


#include "MoonbeamTargetActor.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/BoxComponent.h"
#include "EBAbilitySystemComponent.h"
#include "EBAbilitySystemBlueprintLibrary.h"

AMoonbeamTargetActor::AMoonbeamTargetActor()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	SetRootComponent(RootComp);

	MoonbeamSpringArm = CreateDefaultSubobject<USpringArmComponent>("MoonbeamArm");
	MoonbeamSpringArm->SetupAttachment(GetRootComponent());

	TargetArea = CreateDefaultSubobject<UBoxComponent>("TargetArea");
	TargetArea->SetupAttachment(MoonbeamSpringArm, USpringArmComponent::SocketName);

	PrimaryActorTick.bCanEverTick = true;

	TargetArea->OnComponentBeginOverlap.AddDynamic(this, &AMoonbeamTargetActor::OnOverlap);
	TargetArea->OnComponentEndOverlap.AddDynamic(this, &AMoonbeamTargetActor::OnOverlapEnd);
	TargetArea->SetCollisionResponseToAllChannels(ECR_Ignore);
	TargetArea->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

FVector AMoonbeamTargetActor::GetMoonbeamEndLocation() const
{
	return TargetArea->GetComponentLocation();
}

float AMoonbeamTargetActor::GetMoonbeamLength() const
{
	return (MoonbeamSpringArm->GetComponentLocation() - TargetArea->GetComponentLocation()).Length();
}

void AMoonbeamTargetActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AMoonbeamTargetActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
