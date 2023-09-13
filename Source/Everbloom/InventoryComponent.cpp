// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Weapon.h"
#include "AbilityFlowerItem.h"
#include "EBGameplayAbilityBase.h"
#include "Emilia.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComponent::AddAbilityFlower(UAbilityFlowerItem* FlowerToAdd)
{
	if (!CheckIfFlowerExistsInInventory(FlowerToAdd))
	{
		FlowersObtained.Add(FlowerToAdd);
		//OnNewAbilityFlowerObtained.Broadcast(FlowerToAdd);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Designer, you have two of the same flowers in the world! Remove one!"));
	}
}



float UInventoryComponent::GetCurrentWeaponDamage() const
{
	if (CurrentWeapon)
	{
		return CurrentWeapon->GetWeaponDamage();
	}
	return 0.f;
}


void UInventoryComponent::SetLifedewAmount(int Amount)
{
	Lifedew = FMath::Clamp(Lifedew + Amount, 0, MaxLifedewAmount);
}

TArray<FText> UInventoryComponent::GetFlowerWords() const
{
	if (FlowersObtained.Num() > 0)
	{
		TArray<FText> FlowerWords;
		for (UAbilityFlowerItem* Flower : FlowersObtained)
		{
			FlowerWords.Add(Flower->GetFlowerWord());
		}
		return FlowerWords;
	}
	UE_LOG(LogTemp, Warning, TEXT("No flowers in inventory."));
	return TArray<FText>();
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	GiveStarterMagic();
	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::InitializeInventory(USceneComponent* CompToAttach)
{
	if (!CurrentWeapon && InitialWeaponClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(InitialWeaponClass, SpawnParams);
		FAttachmentTransformRules AttachRules{ EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true };
		CurrentWeapon->AttachToComponent(CompToAttach, AttachRules, CurrentWeapon->GetAttachmentSocketName());
		Weapons.Add(CurrentWeapon);
	}
}

bool UInventoryComponent::CheckIfFlowerExistsInInventory(UAbilityFlowerItem* FlowerToCheck)
{
	for (UAbilityFlowerItem* Flower : FlowersObtained)
	{
		if (Flower->GetClass() == FlowerToCheck->GetClass())
		{
			return true;
		}
	}

	return false;
}

void UInventoryComponent::GiveStarterMagic()
{
	AEmilia* Emilia = Cast<AEmilia>(GetOwner());
	if (Emilia)
	{
		FGameplayAbilitySpec* Spec = Emilia->GiveAbility(StarterWindMagicClass);
		GiveNewMagic(Cast<UEBGameplayAbilityBase>(Spec->Ability));
	}
}

void UInventoryComponent::GiveNewMagic(UEBGameplayAbilityBase* NewAbility)
{
	if (!CurrentMagic)
	{
		CurrentMagic = NewAbility;
	}
	Magic.AddUnique(NewAbility);
}

