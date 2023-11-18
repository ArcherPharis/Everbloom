// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldFlower.h"
#include "EBGameplayAbilityBase.h"
#include "Components/CapsuleComponent.h"
#include "Emilia.h"
#include "Blueprint/UserWidget.h"
#include "DialogueComponent.h"
#include "WorldTreeMenuWidget.h"
#include "InventoryComponent.h"
#include "EBAbilitySystemComponent.h"


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

void AWorldFlower::CreateMenuWidget(AEmilia* WidgetOwnerActor)
{
	APlayerController* PlayerCont = Cast<APlayerController>(WidgetOwnerActor->GetController());
	TreeMenuWidget = CreateWidget<UWorldTreeMenuWidget>(PlayerCont, TreeMenuWidgetClass);
	if (TreeMenuWidget)
	{
		TreeMenuWidget->SetLifedewAmount(WidgetOwnerActor->GetInventoryComponent()->GetLifedews());
		TreeMenuWidget->SetWorldFlowerText(WorldFlowerName);
		TreeMenuWidget->SetSpecialityWidgetParams(SpecialtyText, SpecialityIcon);
		TreeMenuWidget->AddToViewport();
	}
}

void AWorldFlower::CloseMenuWidget()
{
	TreeMenuWidget->RemoveFromParent();
}

void AWorldFlower::CheckCanUpgrade(int ChoiceIndex, AEmilia* Emilia, bool& CanUpgrade)
{
	bool CheckUp;
	switch (ChoiceIndex)
	{
	case 0:
		UE_LOG(LogTemp, Warning, TEXT("Health Logic Here"));
		CanUpgrade = false;
		break;
	case 1:
		CheckUp = Emilia->GetInventoryComponent()->GetLifedews() >= 10;
		CanUpgrade = CheckUp;
		break;
	default: UE_LOG(LogTemp, Warning, TEXT("Out Of Range Index on ChoiceIndex")); break;
	}
}

void AWorldFlower::GiveUpgrade(int ChoiceIndex, AEmilia* Emilia)
{
	switch (ChoiceIndex)
	{
	case 0: UE_LOG(LogTemp, Warning, TEXT("Give Health Effect Boost."));
		break;
	case 1:
		GiveSpecialtyEffect(Emilia);
		break;
	default: break;
	}
}

void AWorldFlower::ChangeToDefaultTree()
{
	DialogueComponent->ChangeDialogueTree(PostSaveDialogueTree);
}

void AWorldFlower::GiveEmiliaWorldFlowerAbility(AEmilia* Player)
{
	Player->GetInventoryComponent()->GiveStandardMagicToInventory(MainAbilityClass);
}

void AWorldFlower::InteractWith(AEmilia* Player)
{
	if (MainAbilityClass)
	{
		//Player->GiveMainAbility(MainAbilityClass, InputValue);
	}
	DialogueComponent->CreateDialogueBox(Player);
	
	
}

void AWorldFlower::GiveSpecialtyEffect(AEmilia* Player)
{
	FGameplayEffectSpecHandle Spec = Player->GetAbilitySystemComponent()->MakeOutgoingSpec(SpecialtyUpgradeEffect, -1, Player->GetAbilitySystemComponent()->MakeEffectContext());
	Player->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*Spec.Data);
	Player->GetInventoryComponent()->SetLifedewAmount(-10);
}

