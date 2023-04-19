// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityFlower.h"
#include "Emilia.h"
#include "AbilityFlowerItem.h"
#include "InventoryComponent.h"

void AAbilityFlower::InteractWith(AEmilia* player)
{
	UInventoryComponent* PlayerInventoryComponent = player->GetInventoryComponent();
	if (PlayerInventoryComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got the flower"));
		UAbilityFlowerItem* Flower = NewObject<UAbilityFlowerItem>(player,GetItemClass());
		PlayerInventoryComponent->AddAbilityFlower(Flower);
	}
	Destroy();
}
