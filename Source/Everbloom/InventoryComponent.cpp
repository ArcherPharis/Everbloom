// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComponent::AddAbilityFlower(AAbilityFlower* FlowerToAdd)
{
	if (!FlowersObtained.Contains(FlowerToAdd))
	{
		FlowersObtained.Add(FlowerToAdd);
		OnNewAbilityFlowerObtained.Broadcast(FlowerToAdd);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Designer, you have two of the same flowers in the world! Remove one!"));
	}
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

