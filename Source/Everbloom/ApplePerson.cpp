// Fill out your copyright notice in the Description page of Project Settings.


#include "ApplePerson.h"
#include "Components/CapsuleComponent.h"
#include "DialogueComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Emilia.h"
#include "InventoryComponent.h"
#include "Weapon.h"

AApplePerson::AApplePerson()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	DialogueComponent = CreateDefaultSubobject<UDialogueComponent>(TEXT("Dialogue Component"));
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
}

void AApplePerson::InteractWith(AEmilia* Player)
{
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Player->GetActorLocation());
	LookAtRot.Pitch = 0.f;
	SetActorRotation(LookAtRot);
	APlayerController* Cont = Cast<APlayerController>(Player->GetController());
	Player->SetActorHiddenInGame(true);
	Player->GetInventoryComponent()->GetCurrentWeapon()->SetActorHiddenInGame(true);
	if (Cont)
	{
		Cont->SetViewTargetWithBlend(this);
		InteractEvent();
	}
	DialogueComponent->CreateDialogueBox(Player);
}
