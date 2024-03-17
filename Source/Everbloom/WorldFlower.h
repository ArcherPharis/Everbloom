// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableInterface.h"
#include "WorldFlower.generated.h"

UCLASS()
class EVERBLOOM_API AWorldFlower : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldFlower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateMenuWidget(AEmilia* WidgetOwnerActor);
	void CloseMenuWidget();
	void CheckCanUpgrade(int ChoiceIndex, AEmilia* Emilia, bool& CanUpgrade);
	void GiveUpgrade(int ChoiceIndex, AEmilia* Emilia);
	void ChangeToDefaultTree();
	void GiveEmiliaWorldFlowerAbility(AEmilia* Player);

	void GetNewGem(AEmilia* Player);


private:
	virtual void InteractWith(AEmilia* Player);
	void GiveSpecialtyEffect(AEmilia* Player);

	UPROPERTY(EditDefaultsOnly, Category = "MainFlower")
	UStaticMeshComponent* FlowerMesh;
	UPROPERTY(EditDefaultsOnly, Category = "MainFlower")
	class UCapsuleComponent* HitCapsule;

	UPROPERTY(EditDefaultsOnly, Category = "MainFlower")
	TSubclassOf<class UEBGameplayAbilityBase> MainAbilityClass;

	UPROPERTY(EditDefaultsOnly, Category = "MainFlower")
	TSubclassOf<class UGem> GemClass;

	UPROPERTY(EditDefaultsOnly, Category = "MainFlower")
	TSubclassOf<class UGameplayEffect> HealthUpgradeEffect;

	UPROPERTY(EditDefaultsOnly, Category = "MainFlower")
	TSubclassOf<class UGameplayEffect> SpecialtyUpgradeEffect;

	UPROPERTY(EditDefaultsOnly, Category = "MainFlower")
	UTexture2D* SpecialityIcon;

	UPROPERTY(EditDefaultsOnly, Category = "MainFlower")
	FText SpecialtyText;

	UPROPERTY(EditDefaultsOnly, Category = "MainFlower")
	int InputValue = 8;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UDialogueComponent* DialogueComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	class UBehaviorTree* PostSaveDialogueTree;

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	FName WorldFlowerName {"Flower Name"};

	UPROPERTY(EditDefaultsOnly, Category = "Dialogue")
	TSubclassOf<class UWorldTreeMenuWidget> TreeMenuWidgetClass;

	UPROPERTY()
	UWorldTreeMenuWidget* TreeMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "MainFlower")
	bool bIsUncorrupted = false;
};
