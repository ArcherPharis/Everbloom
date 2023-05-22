// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_ThunderboltTargetActor.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"
#include "Abilities/GameplayAbilityTargetActor.h"

AGA_ThunderboltTargetActor::AGA_ThunderboltTargetActor()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	SetRootComponent(RootComp);

	TargetArea = CreateDefaultSubobject<USphereComponent>("TargetArea");
	TargetArea->SetupAttachment(RootComp);

	TargetArea->SetCollisionResponseToAllChannels(ECR_Ignore);
	TargetArea->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	PrimaryActorTick.bCanEverTick = true;
}

void AGA_ThunderboltTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
}

void AGA_ThunderboltTargetActor::ConfirmTargetingAndContinue()
{
	TArray<AActor*> overlappingActors;
	TargetArea->GetOverlappingActors(overlappingActors);
	overlappingActors.Remove(OwningAbility->GetAvatarActorFromActorInfo());

	UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActorArray(overlappingActors, false);

	FGameplayAbilityTargetData_LocationInfo* locInfo = new FGameplayAbilityTargetData_LocationInfo;
	locInfo->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	locInfo->TargetLocation.LiteralTransform = GetActorTransform();

	TSharedPtr<FGameplayAbilityTargetData_ActorArray> targetedActorInfo{ new FGameplayAbilityTargetData_ActorArray };
	for (auto actor : overlappingActors)
	{

		targetedActorInfo->TargetActorArray.Add(actor);

	}

	FGameplayAbilityTargetDataHandle TargetDataWithLocInfoAndActors;
	TargetDataWithLocInfoAndActors.Add(locInfo);
	TargetDataWithLocInfoAndActors.Data.Add(targetedActorInfo);

	TargetDataReadyDelegate.Broadcast(TargetDataWithLocInfoAndActors);
}

void AGA_ThunderboltTargetActor::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	if (PrimaryPC)
	{
		
		FVector Loc;
		FRotator Rot;
		PrimaryPC->GetActorEyesViewPoint(Loc, Rot);

		FVector MasterLookDir = UKismetMathLibrary::GetForwardVector(Rot);

		FHitResult hitResult;

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(PrimaryPC->GetPawn()); 

		if (GetWorld()->LineTraceSingleByChannel(hitResult, Loc, Loc + MasterLookDir * TNumericLimits<float>::Max(), ECollisionChannel::ECC_Visibility, Params))
		{
			SetActorLocation(hitResult.Location);
		}
	}
}
