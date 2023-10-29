// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Weapon.h"
#include "AbilityFlowerItem.h"
#include "EBGameplayAbilityBase.h"
#include "Emilia.h"
#include "EBAbilitySystemComponent.h"

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
		Emilia->OnObtainAbilityFlower.Broadcast(FlowerToAdd);
		//OnNewAbilityFlowerObtained.Broadcast(FlowerToAdd);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Designer, you have two of the same flowers in the world! Remove one!"));
	}
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
	Emilia = Cast<AEmilia>(GetOwner());
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
		CurrentWeapon->ApplyWeaponEffect(Emilia);
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

void UInventoryComponent::SpawnNewWeapon(TSubclassOf<AWeapon> NewWeapon, USceneComponent* CompToAttach)
{
	if (NewWeapon)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AWeapon* NewWep = GetWorld()->SpawnActor<AWeapon>(NewWeapon, SpawnParams);
		FAttachmentTransformRules AttachRules{ EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true };
		NewWep->AttachToComponent(CompToAttach, AttachRules, NewWep->GetAttachmentSocketName());
		NewWep->DisableWeapon();
		Weapons.Add(NewWep);
	}
}

void UInventoryComponent::CycleWeapons(float CycleDirection)
{
	if (Weapons.Num() == 0 || Weapons.Num() <= 1)
	{
		return;
	}
	int32 NewIndex = (CurrentWeaponIndex + static_cast<int32>(CycleDirection)) % Weapons.Num();
	if (NewIndex < 0)
	{
		NewIndex = Weapons.Num() - 1;
	}
	CurrentWeapon->DisableWeapon();
	CurrentWeapon->RemoveWeaponEffect(Emilia);
	CurrentWeapon = Weapons[NewIndex];
	CurrentWeapon->EnableWeapon();
	CurrentWeapon->ApplyWeaponEffect(Emilia);
	CurrentWeaponIndex = NewIndex;
	OnChangedWeapon.Broadcast(CurrentWeapon);
}

void UInventoryComponent::CycleMagic(float CycleDirection)
{
	FGameplayAbilitySpec* WindSpec = Emilia->GetAbilitySystemComponent()->FindAbilitySpecFromClass(StarterWindMagicClass);
	if (WindSpec && WindSpec->IsActive())
	{
		return;
	}

	if (Magic.Num() == 0 || Magic.Num() <= 1)
	{
		return;
	}
	int32 NewIndex = (CurrentMagicIndex + static_cast<int32>(CycleDirection)) % Magic.Num();
	if (NewIndex < 0)
	{
		NewIndex = Magic.Num() - 1;
	}
	CurrentMagic = Magic[NewIndex];
	CurrentMagicIndex = NewIndex;
	OnChangedMagic.Broadcast(CurrentMagic);
}

void UInventoryComponent::GiveStarterMagic()
{
	if (Emilia)
	{
		FGameplayAbilitySpec* Spec = Emilia->GiveAbility(StarterWindMagicClass);
		GiveNewMagic(Cast<UEBGameplayAbilityBase>(Spec->Ability));
	}
}

void UInventoryComponent::GiveStandardMagicToInventory(TSubclassOf<UEBGameplayAbilityBase> NewMagic)
{
	if (Emilia)
	{
		FGameplayAbilitySpec* Spec = Emilia->GiveAbility(NewMagic);
		GiveNewMagic(Cast<UEBGameplayAbilityBase>(Spec->Ability));
	}
}

void UInventoryComponent::GiveNewMagic(UEBGameplayAbilityBase* NewAbility)
{
	if (!CurrentMagic)
	{
		CurrentMagic = NewAbility;
		OnChangedMagic.Broadcast(CurrentMagic);
	}
	Magic.AddUnique(NewAbility);
}

